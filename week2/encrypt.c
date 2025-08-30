#include<stdio.h>
#include<math.h>
#include<ctype.h>
#include<string.h>
#include<stdlib.h>

char key[55], text[1000], list[30];

int main()
{
	fgets(key, 55, stdin);
	key[strcspn(key, "\n")] = '\0';
	int keyL = strlen(key);
	FILE *in, *out;
	in = fopen("encrypt.txt", "r"); 
	out = fopen("output.txt", "w");
	
	int used[26] = {0};
	int index = 0;
	for(int i = 0; i < keyL; i++) {
		if(!used[key[i]-'a']) {
			list[index++] = key[i];
			used[key[i]-'a'] = 1;
		}
	}
	for(char c = 'z'; c >= 'a'; c--) {
		if(!used[c - 'a']) {
			list[index++] = c;
		}
	}
	list[index] = '\0';

	while(fgets(text, 1000, in) != NULL) {
		int len = strlen(text);
		for(int i = 0; i < len; i++) {
			if(isalpha(text[i])) {
				text[i] = list[text[i] - 'a'];
			}
		}
		fputs(text, out);
	}
	fclose(in);
	fclose(out);
    return 0;
}
