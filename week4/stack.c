#include<stdio.h>
#include<math.h>
#include<ctype.h>
#include<string.h>
#include<stdlib.h>

int main()
{
	int a[105], top = -1;
	int act, num, index = 0;
	while(scanf("%d", &act) != EOF) {
		if(act == -1) return 0;
		if(act == 0) {
			if(top == -1) printf("error ");
			else printf("%d ", a[top--]);
		} else if(act == 1) {
			if(top == 99) printf("error ");
			else {
				scanf("%d", &num);
				a[++top] = num;
			}
		}
	}
    return 0;
}
