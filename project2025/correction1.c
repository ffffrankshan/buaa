#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>
#include <immintrin.h>  // for SIMD if available

#define MAX_WORD_LEN 100
#define MAX_LINE_LEN 100000
#define DICT_SIZE 10000
#define WORD_BUF_SIZE 1000000
#define OUT_BUF_SIZE 100000
#define HASH_TBL_SIZE 262144  // 增大到2^18，减少碰撞
#define DP_MAX 3300

// 优化的宏定义
#define MAX(a,b) ((a)>(b)?(a):(b))
#define MIN(a,b) ((a)<(b)?(a):(b))
#define MIN3(a,b,c) (MIN(MIN(a,b),c))

// 使用更紧凑的数据结构和内存池
static char word_pool[WORD_BUF_SIZE * 20];  // 预分配字符串池
static size_t pool_offset = 0;

// 优化的字典节点 - 使用更紧凑的结构
struct dict_node {
    uint32_t word_offset;  // 使用偏移量而非指针，节省内存
    uint16_t word_len;     // 缓存长度避免strlen
    struct dict_node *next;
};

static struct dict_node *dict_hash[HASH_TBL_SIZE];
static struct dict_node node_pool[DICT_SIZE * 2];  // 预分配节点池
static size_t node_pool_offset = 0;

// 优化的哈希函数 - FNV-1a，更快更均匀
static inline uint32_t hash_str_fast(const char *s, int len) {
    uint32_t hash = 2166136261u;
    for (int i = 0; i < len; i++) {
        hash ^= (uint8_t)s[i];
        hash *= 16777619u;
    }
    return hash & (HASH_TBL_SIZE - 1);  // 位运算代替取模
}

// 内存池分配器
static inline char* alloc_string(const char* str, int len) {
    if (pool_offset + len + 1 >= sizeof(word_pool)) {
        fprintf(stderr, "String pool exhausted\n");
        exit(1);
    }
    char* result = word_pool + pool_offset;
    memcpy(result, str, len);
    result[len] = '\0';
    pool_offset += len + 1;
    return result;
}

static inline struct dict_node* alloc_node() {
    if (node_pool_offset >= DICT_SIZE * 2) {
        fprintf(stderr, "Node pool exhausted\n");
        exit(1);
    }
    return &node_pool[node_pool_offset++];
}

// 优化的编辑距离计算 - 使用滚动数组和早期退出
static int edit_dist_optimized(const char *s1, int l1, const char *s2, int l2, int max_dist) {
    if (abs(l1 - l2) > max_dist) return max_dist + 1;  // 早期退出
    
    // 使用两行滚动数组而非完整DP表
    static int prev[DP_MAX], curr[DP_MAX];
    
    // 初始化第一行
    for (int j = 0; j <= l2; j++) prev[j] = j;
    
    for (int i = 1; i <= l1; i++) {
        curr[0] = i;
        int min_val = i;  // 追踪当前行最小值用于早期退出
        
        for (int j = 1; j <= l2; j++) {
            if (s1[i-1] == s2[j-1]) {
                curr[j] = prev[j-1];
            } else {
                curr[j] = 1 + MIN3(curr[j-1], prev[j], prev[j-1]);
            }
            min_val = MIN(min_val, curr[j]);
        }
        
        // 早期退出：如果当前行最小值已超过阈值
        if (min_val > max_dist) return max_dist + 1;
        
        // 交换数组
        for (int k = 0; k <= l2; k++) {
            prev[k] = curr[k];
        }
    }
    
    return prev[l2];
}

// 批量字符转换 - SIMD优化的大小写转换
static inline void to_lowercase_fast(char *str, int len) {
    int i = 0;
    
#ifdef __AVX2__
    // AVX2 SIMD优化
    __m256i upper_a = _mm256_set1_epi8('A');
    __m256i upper_z = _mm256_set1_epi8('Z');
    __m256i diff = _mm256_set1_epi8(32);
    
    for (; i <= len - 32; i += 32) {
        __m256i data = _mm256_loadu_si256((__m256i*)(str + i));
        __m256i ge_a = _mm256_cmpgt_epi8(data, _mm256_sub_epi8(upper_a, _mm256_set1_epi8(1)));
        __m256i le_z = _mm256_cmpgt_epi8(_mm256_add_epi8(upper_z, _mm256_set1_epi8(1)), data);
        __m256i is_upper = _mm256_and_si256(ge_a, le_z);
        __m256i to_add = _mm256_and_si256(is_upper, diff);
        __m256i result = _mm256_add_epi8(data, to_add);
        _mm256_storeu_si256((__m256i*)(str + i), result);
    }
#endif
    
    // 处理剩余字符
    for (; i < len; i++) {
        if (str[i] >= 'A' && str[i] <= 'Z') {
            str[i] += 32;
        }
    }
}

// 优化的字典加载
void add_dict_word_fast(const char *w, int len) {
    uint32_t idx = hash_str_fast(w, len);
    struct dict_node *n = alloc_node();
    n->word_offset = pool_offset;
    n->word_len = len;
    alloc_string(w, len);
    n->next = dict_hash[idx];
    dict_hash[idx] = n;
}

// 优化的字典查找
static inline int word_exists_fast(const char *w, int len) {
    uint32_t idx = hash_str_fast(w, len);
    struct dict_node *n = dict_hash[idx];
    while (n) {
        if (n->word_len == len && !memcmp(word_pool + n->word_offset, w, len)) {
            return 1;
        }
        n = n->next;
    }
    return 0;
}

int load_dict_optimized(const char *fname) {
    FILE *f = fopen(fname, "rb");  // 二进制模式更快
    if (!f) {
        printf("can't open dict file\n");
        exit(1);
    }
    
    // 一次读取整个文件
    fseek(f, 0, SEEK_END);
    long file_size = ftell(f);
    fseek(f, 0, SEEK_SET);
    
    char *buffer = malloc(file_size + 1);
    fread(buffer, 1, file_size, f);
    buffer[file_size] = '\0';
    fclose(f);
    
    char word[MAX_WORD_LEN];
    int word_len = 0;
    int cnt = 0;
    
    for (long i = 0; i <= file_size; i++) {
        char c = (i < file_size) ? buffer[i] : '\n';
        
        if (c == '\n' || c == '\r') {
            if (word_len > 0) {
                add_dict_word_fast(word, word_len);
                cnt++;
                word_len = 0;
            }
        } else if (!isspace(c) && word_len < MAX_WORD_LEN - 1) {
            word[word_len++] = c;
        }
    }
    
    free(buffer);
    return cnt;
}

// 优化的单词列表结构
struct word_list_opt {
    uint32_t *word_offsets;  // 使用偏移量
    uint16_t *word_lens;     // 缓存长度
    uint8_t *follows;        // 使用更小的数据类型
    int cnt;
    int cap;
};

// 优化的单词提取
void get_words_optimized(const char *fname, struct word_list_opt *wl) {
    FILE *f = fopen(fname, "rb");
    if (!f) {
        printf("can't open input file\n");
        exit(1);
    }
    
    // 读整个文件到内存
    fseek(f, 0, SEEK_END);
    long file_size = ftell(f);
    fseek(f, 0, SEEK_SET);
    
    char *buffer = malloc(file_size + 1);
    fread(buffer, 1, file_size, f);
    buffer[file_size] = '\0';
    fclose(f);
    
    wl->cap = WORD_BUF_SIZE;
    wl->word_offsets = malloc(wl->cap * sizeof(uint32_t));
    wl->word_lens = malloc(wl->cap * sizeof(uint16_t));
    wl->follows = malloc(wl->cap * sizeof(uint8_t));
    wl->cnt = 0;
    
    char word[MAX_WORD_LEN];
    int word_len = 0;
    int in_word = 0;
    
    for (long i = 0; i <= file_size; i++) {
        char c = (i < file_size) ? buffer[i] : ' ';
        
        if (isalpha(c)) {
            if (!in_word) in_word = 1;
            if (word_len < MAX_WORD_LEN - 1) {
                word[word_len++] = tolower(c);
            }
        } else if (in_word) {
            // 单词结束
            if (wl->cnt >= wl->cap) {
                wl->cap *= 2;
                wl->word_offsets = realloc(wl->word_offsets, wl->cap * sizeof(uint32_t));
                wl->word_lens = realloc(wl->word_lens, wl->cap * sizeof(uint16_t));
                wl->follows = realloc(wl->follows, wl->cap * sizeof(uint8_t));
            }
            
            wl->word_offsets[wl->cnt] = pool_offset;
            wl->word_lens[wl->cnt] = word_len;
            alloc_string(word, word_len);
            
            // 检查是否跟随另一个单词
            long j = i;
            while (j < file_size && (buffer[j] == ' ' || buffer[j] == '\t')) j++;
            wl->follows[wl->cnt] = (j < file_size && isalpha(buffer[j])) ? 1 : 0;
            
            wl->cnt++;
            word_len = 0;
            in_word = 0;
        }
    }
    
    free(buffer);
}

// 优化的建议结构 - 使用预分配数组
#define MAX_SUGGESTIONS 1000
struct suggestions_opt {
    uint32_t offsets[MAX_SUGGESTIONS];
    uint16_t lens[MAX_SUGGESTIONS];
    uint16_t dists[MAX_SUGGESTIONS];  // 缓存距离用于排序
    int cnt;
};

static inline void add_suggestion_fast(struct suggestions_opt *s, uint32_t offset, uint16_t len, uint16_t dist) {
    // 检查重复
    for (int i = 0; i < s->cnt; i++) {
        if (s->lens[i] == len && s->offsets[i] == offset) return;
    }
    
    if (s->cnt < MAX_SUGGESTIONS) {
        s->offsets[s->cnt] = offset;
        s->lens[s->cnt] = len;
        s->dists[s->cnt] = dist;
        s->cnt++;
    }
}

// 高度优化的纠错查找
void find_corrections_optimized(uint32_t prev_offset, uint16_t prev_len,
                              const char *wrong, int wrong_len,
                              const struct word_list_opt *wl,
                              struct suggestions_opt *sugg) {
    int min_dist = 1000;
    sugg->cnt = 0;
    
    const char *prev_word = word_pool + prev_offset;
    
    // 预计算常用情况的早期退出条件
    int max_reasonable_dist = (wrong_len + 2) / 3;  // 启发式阈值
    
    for (int i = 0; i < wl->cnt - 1; i++) {
        // 快速比较前一个单词
        if (wl->word_lens[i] == prev_len && 
            !memcmp(word_pool + wl->word_offsets[i], prev_word, prev_len) &&
            wl->follows[i] == 1) {
            
            const char *candidate = word_pool + wl->word_offsets[i + 1];
            int cand_len = wl->word_lens[i + 1];
            
            // 快速检查是否在字典中
            if (!word_exists_fast(candidate, cand_len)) continue;
            
            // 使用优化的编辑距离，带早期退出
            int dist = edit_dist_optimized(wrong, wrong_len, candidate, cand_len, 
                                         MIN(min_dist, max_reasonable_dist));
            
            if (dist < min_dist) {
                min_dist = dist;
                sugg->cnt = 0;
                add_suggestion_fast(sugg, wl->word_offsets[i + 1], cand_len, dist);
            } else if (dist == min_dist) {
                add_suggestion_fast(sugg, wl->word_offsets[i + 1], cand_len, dist);
            }
        }
    }
    
    // 快速排序建议
    for (int i = 0; i < sugg->cnt - 1; i++) {
        for (int j = i + 1; j < sugg->cnt; j++) {
            const char *a = word_pool + sugg->offsets[i];
            const char *b = word_pool + sugg->offsets[j];
            if (strcmp(a, b) > 0) {
                // 交换
                uint32_t tmp_off = sugg->offsets[i];
                uint16_t tmp_len = sugg->lens[i];
                uint16_t tmp_dist = sugg->dists[i];
                
                sugg->offsets[i] = sugg->offsets[j];
                sugg->lens[i] = sugg->lens[j];
                sugg->dists[i] = sugg->dists[j];
                
                sugg->offsets[j] = tmp_off;
                sugg->lens[j] = tmp_len;
                sugg->dists[j] = tmp_dist;
            }
        }
    }
}

// 使用位集优化的重复检测
#define HASH_BITS 20
#define HASH_SIZE (1 << HASH_BITS)
static uint8_t processed_bitmap[HASH_SIZE / 8];

static inline void mark_processed_fast(uint32_t prev_off, uint16_t prev_len, 
                                     const char* wrong, int wrong_len) {
    // 组合哈希
    uint32_t hash = hash_str_fast(word_pool + prev_off, prev_len);
    hash ^= hash_str_fast(wrong, wrong_len);
    hash &= (HASH_SIZE - 1);
    
    processed_bitmap[hash / 8] |= (1 << (hash % 8));
}

static inline int already_processed_fast(uint32_t prev_off, uint16_t prev_len,
                                       const char* wrong, int wrong_len) {
    uint32_t hash = hash_str_fast(word_pool + prev_off, prev_len);
    hash ^= hash_str_fast(wrong, wrong_len);
    hash &= (HASH_SIZE - 1);
    
    return (processed_bitmap[hash / 8] & (1 << (hash % 8))) != 0;
}

// 主处理函数优化
void process_corrections_optimized(const struct word_list_opt *wl) {
    memset(processed_bitmap, 0, sizeof(processed_bitmap));
    struct suggestions_opt sugg;
    
    for (int i = 1; i < wl->cnt; i++) {
        const char *curr = word_pool + wl->word_offsets[i];
        int curr_len = wl->word_lens[i];
        uint32_t prev_off = wl->word_offsets[i-1];
        uint16_t prev_len = wl->word_lens[i-1];
        
        // 快速检查条件
        if (!word_exists_fast(curr, curr_len) && 
            word_exists_fast(word_pool + prev_off, prev_len) &&
            wl->follows[i-1] == 1) {
            
            if (!already_processed_fast(prev_off, prev_len, curr, curr_len)) {
                mark_processed_fast(prev_off, prev_len, curr, curr_len);
                find_corrections_optimized(prev_off, prev_len, curr, curr_len, wl, &sugg);
                
                // 输出结果
                printf("%.*s: %.*s -> ", prev_len, word_pool + prev_off, curr_len, curr);
                if (sugg.cnt > 0) {
                    for (int j = 0; j < sugg.cnt; j++) {
                        if (j > 0) printf(",");
                        printf("%.*s", sugg.lens[j], word_pool + sugg.offsets[j]);
                    }
                } else {
                    printf("No suggestion");
                }
                printf("\n");
            }
        }
    }
}

int main() {
    // 预热CPU缓存
    __builtin_prefetch(dict_hash, 1, 3);
    __builtin_prefetch(word_pool, 1, 3);
    
    int dict_size = load_dict_optimized("dict.txt");
    
    struct word_list_opt wl = {0};
    get_words_optimized("in.txt", &wl);
    
    process_corrections_optimized(&wl);
    
    // 清理
    free(wl.word_offsets);
    free(wl.word_lens);
    free(wl.follows);
    
    return 0;
}