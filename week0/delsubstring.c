#include<stdio.h>
#include<math.h>
#include<ctype.h>
#include<string.h>
#include<stdlib.h>

int main()
{
	char s[2000], subs[1000];
	fgets(s, sizeof(s), stdin);
	s[strcspn(s, "\n")] = '\0';
	fgets(subs, sizeof(subs), stdin);
	subs[strcspn(subs, "\n")] = '\0';
	int l = strlen(s), subl = strlen(subs);
	char *p;
	while((p = strstr(s, subs)) != NULL)  {
		l -= subl;
		for(int i = p - s; i < l + 1; i++) s[i] = s[i + subl];
		s[l] = '\0';
	}
	printf("%s", s);
    return 0;
}
