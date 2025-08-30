#include <stdio.h>
#include <string.h>

char a[100], b[100];

void deleteZero(char *str)
{
    int len = strlen(str);
    int i = 0;
    while(str[i] == '0' && i < len - 1) {
        i++;
    }
    if(i > 0) {
        for(int j = 0; j < len - i; j++) {
            str[j] = str[i + j];//move
        }
        str[len - i] = '\0';
    }
    if(strlen(str) == 0) {
        str[0] = '0';
        str[1] = '\0';
    }
}

void reverse(char *str)
{
    int len = strlen(str);
    for (int i = 0; i < len / 2; i++) {
        char tmp = str[i];
        str[i] = str[len - i - 1];
        str[len - i - 1] = tmp;
    }
}

int main()
{
    fgets(a, 81, stdin);
    fgets(b, 81, stdin);
    a[strcspn(a, "\n")] = '\0';
    b[strcspn(b, "\n")] = '\0';
    int len1 = strlen(a);
    int len2 = strlen(b);
    deleteZero(a);
    deleteZero(b);
    char ans[200] = {0};
    if(len1 > len2 || (len1 == len2 && strcmp(a, b) > 0)) {//a-b
        int borrow = 0;
        for(int i = 0; i < len1; ++i) {
            int digit1 = a[len1 - 1 - i] - '0';
            int digit2 = i < len2 ? b[len2 - 1 - i] - '0' : 0;
            int result = digit1 - digit2 - borrow;
            if(result < 0) {
                result += 10;
                borrow = 1;
            } else {
                borrow = 0;
            }
            ans[i] = result + '0';
        }
        reverse(ans);
        deleteZero(ans);
        printf("%s", ans);
    } else {//b-a
        int borrow = 0;
        for (int i = 0; i < len2; ++i) {
            int digit1 = b[len2 - 1 - i] - '0';
            int digit2 = i < len1 ? a[len1 - 1 - i] - '0' : 0;
            int result = digit1 - digit2 - borrow;
            if (result < 0) {
                result += 10;
                borrow = 1;
            } else {
                borrow = 0;
            }
            ans[i] = result + '0';
        }
        reverse(ans);
        deleteZero(ans);
        if(ans[0] == '0') {
            printf("0");
        } else {
            printf("-%s", ans);
        }
    }
    return 0;
}