#include<stdio.h>
#include<math.h>
#include<ctype.h>
#include<string.h>
#include<stdlib.h>

char text[5000], result[5000];

int main()
{
	FILE *in, *out;
	in = fopen("fcopy.in", "r"); 
	out = fopen("fcopy.out", "w");
	while(fgets(text, 5000, in) != NULL) {
		int len = strlen(text);
		int j = 0;
		for(int i = 0; i < len; i++)
			if(text[i] == '\t') text[i] = ' ';
		for(int i = 0; i < len; i++) {
			if(text[i] != ' ' || (text[i+1] != ' ' && i+1 < len)) {
				result[j++] = text[i];
			}
		}
		result[j] = '\0';
		fputs(result, out);
	}
	fclose(in);
	fclose(out);
    return 0;
}
