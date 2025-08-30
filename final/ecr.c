#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

struct dish {
	int id;
	char name[22];
	int num;
	int price;
	int sell;
};

int cmp(const void *p1, const void *p2) {
	struct dish *d1 = (struct dish *)p1;
    struct dish *d2 = (struct dish *)p2; 
    if(d1->sell > d2->sell) return -1;
    else if(d1->sell < d2->sell) return 1;
    else {
    	if(d1->num > d2->num) return -1;
    	else if(d1->num < d2->num) return 1;
	}
    return 0;
}

int main()
{
	int n;
	scanf("%d", &n);
	struct dish a[105];
	int count = 0, sum = 0;
    for(int i = 0; i < n; i++) {
        int id;
		char name[22];
        int num;
        int price;
        scanf("%d %s %d %d", &id, name, &num, &price);
        sum += num * price;
        int found = 0;
        for(int j = 0; j < count; j++) {
            if(strcmp(a[j].name, name) == 0) {
                a[j].num += num;
                a[j].sell += num*price;
                found = 1;
                break;
            }
        }
        if(!found) {
            a[count].id = id;
            strcpy(a[count].name, name);
            a[count].num = num;
            a[count].price = price;
            a[count].sell = num*price;
            count++;
        }
    }
    printf("%d\n", sum);
	qsort(a, count, sizeof(struct dish), cmp);
	for(int i = 0; i < count; i++) printf("%s %d %d\n", a[i].name, a[i].num, a[i].sell);
    return 0;
}
