#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

typedef struct info info;
struct info {
    char c;
    char title[105];
    char date[10];
};

info stkE[105], stkD[105], stkC[105], ans[105];
int topE = -1, topD = -1, topC = -1;

int main()
{
	int idx = 0;
	while(1) {
		char c;
		scanf("%c", &c);
		if(c == 'R') break;
		else if(c == 'E') {
			char s[210], s1[105], s2[105];
    		fgets(s, 210, stdin);
    		s[strcspn(s, "\n")] = '\0';
    		sscanf(s, "%s %s", s1, s2);
    		++topE;
    		stkE[topE].c = c;
    		strcpy(stkE[topE].title, s1);
    		strcpy(stkE[topE].date, s2);
		} else if(c == 'D') {
			char s[210], s1[105], s2[105];
    		fgets(s, 210, stdin);
    		s[strcspn(s, "\n")] = '\0';
    		sscanf(s, "%s %s", s1, s2);
    		++topD;
    		stkD[topD].c = c;
    		strcpy(stkD[topD].title, s1);
    		strcpy(stkD[topD].date, s2);
		} else if(c == 'C') {
			char s[210], s1[105], s2[105];
    		fgets(s, 210, stdin);
    		s[strcspn(s, "\n")] = '\0';
    		sscanf(s, "%s %s", s1, s2);
    		++topC;
    		stkC[topC].c = c;
    		strcpy(stkC[topC].title, s1);
    		strcpy(stkC[topC].date, s2);
		} else if(c == 'S') {
			int n;
			scanf("%d", &n);

			while(topE > -1 && n > 0) {
				ans[idx++] = stkE[topE--];
				n--;
			}
			while(topD > -1 && n > 0) {
				ans[idx++] = stkD[topD--];
				n--;
			}
			while(topC > -1 && n > 0) {
				ans[idx++] = stkC[topC--];
				n--;
			}
		}
	}
	for(int i = 0; i < idx; i++) printf("%c %s %s\n", ans[i].c, ans[i].title, ans[i].date);
	
	for(int i = topE; i >= 0; i--) printf("%c %s %s\n", stkE[i].c, stkE[i].title, stkE[i].date);
	for(int i = topD; i >= 0; i--) printf("%c %s %s\n", stkD[i].c, stkD[i].title, stkD[i].date);
	for(int i = topC; i >= 0; i--) printf("%c %s %s\n", stkC[i].c, stkC[i].title, stkC[i].date);
    return 0;
}
