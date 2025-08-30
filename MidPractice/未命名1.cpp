#include<stdio.h>
#include<string.h>
char s[105][105];

int query(char s[]) {
    int cnt[30] = {0};
    int len = strlen(s);
    for(int i = 0; i < len; i++) {
        cnt[s[i] - 'a']++;
    }
    int max = 0;
    for(int i = 0; i <= 25; i++) {
        if(cnt[i] > max) max = cnt[i];
    }
    return max;
}

int main()
{
    int n, sum;
    scanf("%d%d", &n, &sum);
    for(int i = 0; i < n; i++) {
    	fgets(s[i], 105, stdin);
    	s[i][strcspn(s[i], "\n")] = '\0';
	}
    
    for(int i = 0; i < sum; i++) {
        char input[120];
		char act[10], rest[110];
        fgets(input, 120, stdin);
    	input[strcspn(input, "\n")] = '\0';
        sscanf(input, "%s %s", act, rest);
        if(act[0] == 'm') {
            int src, dest;
            sscanf(rest, "%d %d", &src, &dest);
            strcat(s[dest], s[src]);
            s[src] = '\0';
        } else if(act[0] == 'a') {
            int dest;
            char suf[105];
            sscanf(rest, "%d %s", &dest, suf);
            strcat(s[dest], suf);
        } else if(act[0] == 'd') {
            int dest, k;
            sscanf(rest, "%d %d", &dest, &k);
            int len = strlen(s[dest]);
            if(len < k) s[dest] = '\0';
            else s[dest][len-k] = '\0';
        } else if(act[0] == 'q') {
            int src;
            sscanf(rest, "%d", &src);
            printf("%d\n", query(s[src]));
        } else if(act[0] == 'p') {
            int src;
            sscanf(rest, "%d", &src);
            printf("%s\n", s[src]);
        }
    }
    return 0;
}