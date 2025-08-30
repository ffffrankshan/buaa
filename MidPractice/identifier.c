#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

struct id {
    char s[35];
};

int cmp(const void *p1, const void *p2) {
    struct id *d1 = (struct id *)p1;
    struct id *d2 = (struct id *)p2; 
    return strcmp(d1->s, d2->s);
}

int main() {
    char str[205];
    fgets(str, 205, stdin);
    str[strcspn(str, "\n")] = '\0';
    int l = strlen(str);

    struct id a[52];
    int index = 0;
    char *start = str;
    for (int i = 0; i < l;) {
        int len = 0;
        if (isalpha(str[i]) || str[i] == '_') {
            while (i < l && (isalnum(str[i]) || str[i] == '_')) {
                len++;
                i++;
            }
            // 复制标识符到结构体数组
            if (len < 35) {
                strncpy(a[index].s, start, len);
                a[index].s[len] = '\0';
                index++;
            }
            start += len;
        } else {
            // 跳过非标识符字符
            start++;
            i++;
        }
    }

    if (index == 0) {
        return 0;
    }

    // 排序标识符
    qsort(a, index, sizeof(struct id), cmp);

    // 去重
    int j = 0;
    for (int i = 0; i < index; i++) {
        if (i == 0 || strcmp(a[i].s, a[i-1].s) != 0) {
            a[j++] = a[i];
        }
    }

    for (int i = 0; i < j; i++) {
        if (!isdigit(a[i].s[0])) {
            printf("%s ", a[i].s);
        }
    }
    return 0;
}