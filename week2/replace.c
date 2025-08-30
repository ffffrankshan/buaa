#include<stdio.h>
#include<math.h>
#include<ctype.h>
#include<string.h>
#include<stdlib.h>

char *Strstr(const char *str, const char *target) {
    for(; *str; str++) {
        if(tolower(*str) == tolower(*target)) {
            const char *h = str;
            const char *n = target;
            while (*h && *n && tolower(*h) == tolower(*n)) {
                h++;
                n++;
            }
            if(!*n) return (char *)str;//reach target end
        }
    }
    return NULL;
}

int main()
{
	char a[1000], b[1000];
	fgets(a, 1000, stdin);
    a[strcspn(a, "\n")] = '\0';
    fgets(b, 1000, stdin);
    b[strcspn(b, "\n")] = '\0';
	int len1 = strlen(a), len2 = strlen(b);
	FILE *in, *out;
	in = fopen("filein.txt", "r"); 
	out = fopen("fileout.txt", "w");
	char s[2000];
	while(fgets(s, 2000, in) != NULL) {
		char *start = s;
		char *p;
		while((p = Strstr(start, a)) != NULL) {
            int len = p - start;
            fwrite(start, 1, len, out);//before
            fwrite(b, 1, len2, out);//replace
            start = p + len1;//next round
		}
		fputs(start, out);//after
	}
	fclose(in);
	fclose(out);
    return 0;
}
