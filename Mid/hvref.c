#include<stdio.h>
#include<math.h>
#include<ctype.h>
#include<string.h>
#include<stdlib.h>

int main()
{
	char s[10005];
	char *p = s;
    fgets(s, 10005, stdin);
    s[strcspn(s, "\n")] = '\0';

	int len = strlen(s);
	char file[105][40];
	int num = -1;
	for(int i = 0; i < len;) {
		if(s[i] == '(') {
			int l = 0;
			while(s[i+1+l] != ')') {
				l++;
			}
			char str[40];
			strncpy(str, p+i+1, l);
			str[l] = '\0';
			for(int j = 0; j < l-1; j++) {
				if(str[j] == ',') {
					str[j] = ' ';
					for(int k = j+1; k < l-1; k++) {
						str[k] = str[k+1];
					}
					str[l-1] = '\0';
					break;
				}
			}
			int flag = 0;
			if(num == -1) strcpy(file[++num], str);
			for(int j = 0; j <= num; j++) {
				if(strcmp(str, file[j]) == 0) flag = 1;
			}
			if(!flag) {
				strcpy(file[++num], str);
			}
			i += l+2;
		} else i++;
	}
	for(int i = 0; i <= num; i++) printf("%s\n", file[i]);
    return 0;
}
