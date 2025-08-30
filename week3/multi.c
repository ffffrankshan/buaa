#include<stdio.h>
#include<math.h>
#include<ctype.h>
#include<string.h>
#include<stdlib.h>

struct Node {
	int coe;
	int pow;
	struct Node *next;
};

int main()
{
	char c;
	struct Node p[100], q[100], ans[200];
	int len1 = 0, len2 = 0;
	do {
		scanf("%d%d%c", &p[len1].coe, &p[len1].pow, &c);
		len1++;
	} while(c != '\n');
	do {
		scanf("%d%d%c", &q[len2].coe, &q[len2].pow, &c);
		len2++;
	} while(c != '\n');
	
	int len = 0;
	//all
	for(int i = 0; i < len1; i++) {
		for(int j = 0; j < len2; j++) {
			ans[len].coe = p[i].coe * q[j].coe;
			ans[len++].pow = p[i].pow + q[j].pow;
		}
	}
	//add
	for(int i = 0; i < len - 1; i++) {
		for(int j = i+1; j < len; j++) {
			if(ans[i].pow == ans[j].pow) {
				ans[i].coe += ans[j].coe;
				ans[j].coe = 0;//erase
			}
		}
	}
	//sort
	for(int i = 0; i < len-1; i++) {
		for(int j = 0; j < len-1-i; j++) {
			struct Node temp;
			if(ans[j].pow < ans[j+1].pow) {
				temp = ans[j];
				ans[j] = ans[j+1];
				ans[j+1] = temp;
			}
		}
	}
	for(int i = 0; i < len; i++) {
		if(ans[i].coe != 0) {//easy
			printf("%d %d ", ans[i].coe, ans[i].pow);
		}
	}
    return 0;
}
