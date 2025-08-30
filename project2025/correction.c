#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORD_LENGTH 100
#define MAX_LINE_LENGTH 100000
#define INITIAL_DICT_SIZE 10000
#define INITIAL_WORD_BUFFER 1000000
#define INITIAL_OUT_BUFFER 100000
#define max2(a,b) ((a)>(b)?(a):(b))

int **Dp, MaxDP=3300;
int min3(int a, int b, int c)
{
    int min = a < b ? a : b;
    return min < c ? min : c;
}

int error2(char *s)
{
    fprintf(stderr,"%s\n",s); 
    exit(-1); 
}

int initDP()
{
    int i;
    Dp = (int **)malloc(MaxDP*sizeof(int *));
    for(i=0; i<MaxDP; i++)
        Dp[i] = (int *)malloc(MaxDP*sizeof(int));
    return 0;    
}

int editdistDP(char *str1, char *str2) 
{
    int i,j;
    int len1, len2;
    static int flag=0;
    
    (flag++) ? 1 : initDP(); 
    len1 = strlen(str1)+1; len2 = strlen(str2)+1;
    (max2(len1,len2)>=MaxDP) ? error2("DP memory error!") : len1;
    for (i=0; i<=len1; i++) {
        for (j=0; j<=len2; j++) {
            if (i==0)
                Dp[i][j] = j;
            else if (j==0)
                Dp[i][j] = i;
            else if (str1[i-1] == str2[j-1])
                Dp[i][j] = Dp[i-1][j-1];
            else
                Dp[i][j] = 1 + min3(Dp[i][j-1], Dp[i-1][j], Dp[i-1][j-1]);
        }
    }
    return Dp[len1][len2];
}

int flag[MAX_LINE_LENGTH];
int cmp(const void *a, const void *b) 
{
    const char *str1 = *(const char **)a;
    const char *str2 = *(const char **)b;
    return strcmp(str1, str2);
}

int read_dict(const char *filename, char ***dict) 
{
    FILE *file = fopen(filename, "r");
    int capacity = INITIAL_DICT_SIZE;
    *dict = (char **)malloc(capacity * sizeof(char *));
    int count = 0;
    char line[MAX_LINE_LENGTH];
    while (fgets(line, sizeof(line), file)) 
	{
        int len = strlen(line);
        while (len > 0 && isspace(line[len - 1])) 
		{
            line[--len] = '\0';
        }
        if (len > 0) {
            if (count >= capacity) {
                capacity *= 2;
                *dict = (char **)realloc(*dict, capacity * sizeof(char *));
                
            }
            (*dict)[count] = (char *)malloc((len + 1) * sizeof(char));
            strcpy((*dict)[count], line);
            count++;
        }
    }
    fclose(file);
    qsort(*dict, count, sizeof(char*), cmp);
    return count;
}

int check(const char *word, char **dict, int dict_size) 
{
	char **result = (char **)bsearch(&word,dict,dict_size, sizeof(char *),cmp);
    if (result != NULL) return 1;
    return 0;
}

void find_suggestions(const char *prev_word, const char *wrong_word, char **words, int word_count, char **dict, int dict_size, char ***suggestions, int *suggestion_count, int *flag) 
{
    int min_distance = 10000;
    *suggestion_count = 0;
    *suggestions = NULL;
    for (int i = 0; i < word_count - 1; i++) 
	{
        if (strcmp(words[i], prev_word) == 0 && flag[i]==1 && check(words[i+1], dict, dict_size)) 
        {
            char *correct_word = words[i + 1];
            int distance = editdistDP(wrong_word, correct_word);
            if (distance < min_distance) 
			{
                min_distance = distance;
                *suggestions = (char **)malloc(sizeof(char *));             
                (*suggestions)[0] = (char *)malloc((strlen(correct_word) + 1) * sizeof(char));                
                strcpy((*suggestions)[0], correct_word);
                *suggestion_count = 1;
            } 
            else if (distance == min_distance) 
			{
                int flag2 = 0;
                for (int r = 0; r < *suggestion_count; r++) 
				{
                    if (strcmp((*suggestions)[r], correct_word) == 0) 
					{
                        flag2 = 1;
                        break;
                    }
                }
                if (flag2 == 1) continue;
                *suggestions = (char **)realloc(*suggestions, (*suggestion_count + 1) * sizeof(char *));
                (*suggestions)[*suggestion_count] = (char *)malloc((strlen(correct_word) + 1) * sizeof(char));
                strcpy((*suggestions)[*suggestion_count], correct_word);
                (*suggestion_count)++;
            }
        }
    }
    for (int i = 0; i < *suggestion_count - 1; i++) 
	{
        for (int j = i + 1; j < *suggestion_count; j++) 
		{
            if (strcmp((*suggestions)[i], (*suggestions)[j]) > 0) 
			{
                char *temp = (*suggestions)[i];
                (*suggestions)[i] = (*suggestions)[j];
                (*suggestions)[j] = temp;
            }
        }
    }
}

void process_text(const char *filename1, char **dict, int dict_size) 
{
    FILE *file1 = fopen(filename1, "r");
    int estimated_words = INITIAL_WORD_BUFFER;
    char **words = (char **)malloc(estimated_words * sizeof(char *));  
    int *flag = (int *)malloc(estimated_words* sizeof(int));
    int word_count = 0;
    char line[MAX_LINE_LENGTH];
    while (fgets(line, sizeof(line), file1))
	{
        int l = strlen(line);
        int t1 = 0, flag1 = 0;
        char *word = (char *)malloc(MAX_WORD_LENGTH);       
        for (int i = 0; i < l; i++) {
            if (islower(line[i])) {
                flag1 = 1;
                word[t1++] = line[i];
            }
            else if (isupper(line[i])) {
                flag1 = 1;
                word[t1++] = line[i] - 'A' + 'a';
            }
            else if (line[i] == ' ' || line[i] == '\t') 
			{
                if (flag1 == 1) 
				{
                    word[t1] = '\0';
                    flag1 = 0;
                    
                    if (word_count >= estimated_words) 
					{
                        estimated_words *= 2;
                        words = (char **)realloc(words, estimated_words * sizeof(char *));
                        flag = (int *)realloc(flag, estimated_words * sizeof(int));
                    }
                    
                    words[word_count] = (char *)malloc((strlen(word) + 1) * sizeof(char));                   
                    strcpy(words[word_count], word);
                    while(line[i+1] == ' ' || line[i+1] == '\t')
                    {
                    	i++;
					}
                    if ((i+1 < l) && (islower(line[i+1]) || isupper(line[i+1]))) 
					{
                        flag[word_count] = 1;
                    } 
                    
                    word_count++;
                    memset(word, '\0', t1);
                    t1 = 0;
                }
            }
            else 
			{
                if (flag1 == 1) 
				{
                    word[t1] = '\0';
                    flag1 = 0;
                    
                    if (word_count >= estimated_words) 
					{
                        estimated_words *= 2;
                        words = (char **)realloc(words, estimated_words * sizeof(char *));
                        flag = (int *)realloc(flag, estimated_words * sizeof(int));
                    }
                    
                    words[word_count] = (char *)malloc((strlen(word) + 1) * sizeof(char));          
                    strcpy(words[word_count], word);
                    word_count++;
                    
                    memset(word, '\0', t1);
                    t1 = 0;
                }
            }
        }
    }
    fclose(file1);
    
    int out_count = 0;
    char *out1[INITIAL_OUT_BUFFER];
    char *out2[INITIAL_OUT_BUFFER]; 
    
    for (int i = 1; i < word_count; i++) 
	{
        if (!check(words[i], dict, dict_size) && check(words[i - 1], dict, dict_size) && flag[i-1] == 1)  
        {
            int flag3 = 0;
            for (int w = 0; w < out_count; w++) 
			{
                if (strcmp(out1[w], words[i - 1]) == 0 && strcmp(out2[w], words[i]) == 0) 
				{
                    flag3 = 1;
                    break;
                }
            }
            if (flag3 == 0) 
			{
                out1[out_count] = (char *)malloc(MAX_WORD_LENGTH + 1);
                out2[out_count] = (char *)malloc(MAX_WORD_LENGTH + 1);
            
                strcpy(out1[out_count], words[i - 1]);
                strcpy(out2[out_count], words[i]);
                out_count++;
                
                char **suggestions = NULL;
                int suggestion_count = 0;
                find_suggestions(words[i - 1], words[i], words, word_count, dict, dict_size, &suggestions, &suggestion_count, flag);
                
                if (suggestion_count > 0) 
				{
                    printf("%s: %s -> ", words[i - 1], words[i]);
                    for (int j = 0; j < suggestion_count; j++) 
					{
                        if (j > 0) 
						{
                            printf(",");
                        }
                        printf("%s", suggestions[j]);
                    }
                    printf("\n");
                } 
				else
				{
                	printf("%s: %s -> No suggestion\n", words[i - 1], words[i]);
                }
            }
        }
    }
}

int main() 
{
    char **dict;
    int dict_size = read_dict("dict.txt", &dict);  
    process_text("in.txt", dict, dict_size);
    for (int i = 0; i < dict_size; i++) 
	{
        free(dict[i]);
    }
    free(dict);
    return 0;
}

