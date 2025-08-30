#include<stdio.h>
#include<math.h>
#include<ctype.h>
#include<string.h>
#include<stdlib.h>

int main()
{
	int x;
	scanf("%d", &x);
	for(int j = 1; j < x; j++) {
		int sum = 0;
		for(int i = j; i < x; i++) {
			sum += i;
			if(sum > x) {
				break;
			} else if(sum == x) {
				printf("%d=", x);
				for(int k = j; k <= i-1; k++) printf("%d+", k);
				printf("%d", i);
				return 0;
			}
		}	
	}
	printf("No Answer");
    return 0;
}
