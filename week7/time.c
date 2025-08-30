#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

struct stu {
	int id;
	char name[22];
	int time;
};

int cmp(const void *p1, const void *p2) {
	struct stu *d1 = (struct stu *)p1;
    struct stu *d2 = (struct stu *)p2; 
    if(d1->time > d2->time) return -1;
    else if(d1->time < d2->time) return 1;
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
	struct stu a[105];
	int count = 0;
    for(int i = 0; i < n; i++) {
        int id;
		char name[22];
        int time;
        scanf("%d %s %d", &id, name, &time);
        
        int found = 0;
        for(int j = 0; j < count; j++) {
            if(a[j].id == id) {
                a[j].time += time;
                found = 1;
                break;
            }
        }
        if(!found) {
            a[count].id = id;
            strcpy(a[count].name, name);
            a[count].time = time;
            count++;
        }
    }
	qsort(a, count, sizeof(struct stu), cmp);
	for(int i = 0; i < count; i++) printf("%d %s %d\n", a[i].id, a[i].name, a[i].time);
    return 0;
}
