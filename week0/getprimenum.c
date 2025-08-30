#include<stdio.h>
#include<math.h>
#include<ctype.h>
#include<string.h>
#include<stdlib.h>

int is_prime(int x) {
    if (x < 2) return 0;
    for (int i = 2; i * i <= x; i++) {
        if (x % i == 0) return 0;
    }
    return 1;
}

int reverse(int x) {
	int x1 = 0, digit;
	while(x) {
		digit = x % 10;
		x1 = x1*10 + digit;
		x /= 10;
	}
	return x1;
}

int judge(int x) {
	if(is_prime(x) && is_prime(reverse(x))) return 1;
	return 0;
}

int main()
{
	int n;
	scanf("%d", &n);
	if(judge(n)) printf("yes");
	else printf("no");
    return 0;
}
