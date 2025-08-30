#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

int main()
{
	int n;
	scanf("%d", &n);

	char s[105];
    fgets(s, 105, stdin);
    s[strcspn(s, "\n")] = '\0';

	FILE *in = fopen(".txt", "r");
	FILE *out = fopen(".txt", "w");
	while(fgets(s, 105, in) != NULL)
	fclose(in);
	fclose(out);
    return 0;
}
