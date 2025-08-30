#include<stdio.h>
#include<math.h>
#include<ctype.h>
#include<string.h>
#include<stdlib.h>

int main()
{
	char line[1000];
	int count[26] = {0};
	while(fgets(line, sizeof(line), stdin) != NULL) {
		int l = strlen(line);
		for(int i = 0; i < l; i++) {
			if(islower(line[i])) count[line[i]-'a']++;
		}	
	}
	int max = 0;
	for(int i = 0; i < 26; i++) {
		if(count[i] > max) max = count[i];
	}
	for(int i = max; i >= 1; i--) {
		for(int j = 0; j < 26; j++) {
			if(count[j] >= i) printf("*");
			else printf(" ");
		}
		printf("\n");
	}
	printf("abcdefghijklmnopqrstuvwxyz");
    return 0;
}
