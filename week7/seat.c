#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

struct list {
	int id;
	char name[21];
	int num;
};

int cmp1(const void *p1, const void *p2) {
	struct list *d1 = (struct list *)p1;
    struct list *d2 = (struct list *)p2; 
    if(d1->num < d2->num) return -1;
    else if(d1->num > d2->num) return 1;
    return 0;
}

int cmp2(const void *p1, const void *p2) {
	struct list *d1 = (struct list *)p1;
    struct list *d2 = (struct list *)p2; 
    if(d1->num < d2->num) return -1;
    else if(d1->num > d2->num) return 1;
    else {
    	if(d1->id > d2->id) return -1;
    	else if(d1->id < d2->id) return 1;
	}
    return 0;
}

int cmp3(const void *p1, const void *p2) {
	struct list *d1 = (struct list *)p1;
    struct list *d2 = (struct list *)p2; 
    if(d1->id < d2->id) return -1;
    else if(d1->id > d2->id) return 1;
    return 0;
}

int main()
{
	int n;
	scanf("%d", &n);
	FILE *in = fopen("in.txt", "r");
	FILE *out = fopen("out.txt", "w");
	struct list a[105];
	int i = 0;
	char s[50];
	while(fgets(s, 50, in) != NULL) {
		s[strcspn(s, "\n")] = '\0';
		sscanf(s, "%d %s %d\n", &a[i].id, a[i].name, &a[i].num);
		i++;
	}
	qsort(a, n, sizeof(struct list), cmp1);

	int flag[105] = {0};
	for(int j = 0; j < n; j++) {
		flag[a[j].num]++;
	}
	int m = a[n-1].num;
	int q = (m<n) ? m : n;
	int k = 0;
	for(int j = 1; j <= q; j++) {//num
		if(flag[j] == 0) {
			a[n-1-k].num = j;
			k++;
		}
	}
	qsort(a, n, sizeof(struct list), cmp2);
	memset(flag, 0, sizeof(flag));
	for(int j = 0; j < n; j++) {
		flag[a[j].num]++;
	}

	m = a[n-1].num;
	k = 1;
	for(int j = 0; j < n; j++) {//index
		if(flag[a[j].num] > 1) {
			flag[a[j].num]--;
			a[j].num = m+k;
			k++;
		}
	}
	qsort(a, n, sizeof(struct list), cmp3);
	char ans[50];
	for(int j = 0; j < n; j++) {
		sprintf(ans, "%d %s %d\n", a[j].id, a[j].name, a[j].num);
		fputs(ans, out);
	}
	fclose(in);
	fclose(out);
    return 0;
}
