#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

struct list {
	char num[12];
	char id;
	char t1[7], t2[7];
};
struct list ans[1005];
int index = 0;

void search(struct list a[], int len, char *target, char *target1, char *target2, char id)
{
    for(int i = 0; i < len; i++) {
    	if(strcmp(a[i].num, target) == 0) continue;
		if(strcmp(a[i].t2, target1) >= 0 && strcmp(a[i].t1, target2) <= 0) {
    		if(a[i].id == id) {
    			ans[index].id = a[i].id;
            	strcpy(ans[index].num, a[i].num);
            	index++;
			}
		}
	}
}

int cmp(const void *p1, const void *p2) {
	struct list *d1 = (struct list *)p1;
    struct list *d2 = (struct list *)p2; 
    if(strcmp(d1->num, d2->num) < 0) return -1;
    else if(strcmp(d1->num, d2->num) > 0) return 1;
    else {
    	if(d1->id < d2->id) return -1;
    	else if(d1->id > d2->id) return 1;
	}
    return 0;
}

int main()
{
	int n;
	scanf("%d", &n);
	getchar();
	struct list a[1005];
	for(int i = 0; i < n; i++) {
		scanf("%s %c %s %s ", a[i].num, &a[i].id, a[i].t1, a[i].t2);
	}
	char target[12];
    fgets(target, 12, stdin);
    target[strcspn(target, "\n")] = '\0';
    
    char tar1[7], tar2[7];
	for(int i = 0; i < n; i++) {
    	if(strcmp(a[i].num, target) == 0) {
    		strcpy(tar1, a[i].t1);
    		strcpy(tar2, a[i].t2);
    		search(a, n, target, tar1, tar2, a[i].id);
		}
	}
	
    qsort(ans, index, sizeof(struct list), cmp);
    for(int i = 0; i < index; i++) {
    	if(i > 0 && ans[i].id == ans[i-1].id && strcmp(ans[i].num, ans[i-1].num) == 0)
    		continue;
    	printf("%s %c\n", ans[i].num, ans[i].id);	
	}
    return 0;
}
