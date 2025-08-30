#include<stdio.h>
#include<ctype.h>
#include<string.h>
#include<stdlib.h>
int a[12][12];
int main()
{
	int n;
	
	scanf("%d", &n);
	for(int i = 0; i < n; i++)
		for(int j = 0; j < n; j++) 
			scanf("%d", &a[i][j]);
	while(1) {
		char c;
		scanf(" %c", &c);
		if(c == '#') break;
		for(int i = 0; i < n; i++) {
			for(int j = 0; j < n; j++) {
				int x;
				scanf("%d", &x);
				if(c == '+') a[i][j] += x;
				if(c == '-') a[i][j] -= x;
			}
		}
	}
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < n; j++)
			printf("%5d", a[i][j]);
		printf("\n");
	}
    return 0;
}
