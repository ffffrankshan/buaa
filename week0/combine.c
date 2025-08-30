#include<stdio.h>
#include<math.h>
#include<ctype.h>
#include<string.h>
#include<stdlib.h>

int c[205];
void str_bin(char str1[ ], char str2[ ], int len1, int len2)
{
	for(int i = 0; i < len1; i++) c[i] = str1[i];
	for(int i = 0; i < len2; i++) c[len1+i] = str2[i];
	for(int i = 0; i < len1 + len2 - 1; i++) {
        for(int j = 0; j < len1 + len2 - i - 1; j++){
            if(c[j] > c[j + 1]) {
                int temp = c[j];
                c[j] = c[j + 1];
                c[j + 1] = temp;
            }
        }
    }
}

int main()
{
	char str1[105], str2[105];
	scanf("%s%s", str1, str2);
	int len1 = strlen(str1);
	int len2 = strlen(str2);
	str_bin(str1, str2, len1, len2);
	for(int i = 0; i < len1+len2; i++) printf("%c", c[i]);
    return 0;
}
