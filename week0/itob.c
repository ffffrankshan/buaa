#include<stdio.h>
#include<math.h>
#include<ctype.h>
#include<string.h>
#include<stdlib.h>

char digit[40] = "0123456789abcdefghijklmnopqrstuvwxyz";

void itob(int n, char *s, int b)
{
	int sign = 1;
	if(n < 0) {
		n = -n;
		sign = 0;
	}
	int i = 0;	
	while(n) {
		s[i++] = digit[n % b];
		n /= b;
	}
	if(sign == 0) {
		s[i++] = '-';
	}
	s[i] = '\0';
	int len = strlen(s);
    for(int j = 0; j < len / 2; j++) {
        char temp = s[j];
        s[j] = s[len - j - 1];
        s[len - j - 1] = temp;
    }
}

int main()
{
	int n, b;
	char s[100];
	scanf("%d%d", &n, &b);
	itob(n, s, b);
	printf("%s", s);
    return 0;
}
