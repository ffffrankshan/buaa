#include<stdio.h>
#include<stdlib.h>

struct Circle {
    int pos;
    int len;
    struct Circle *last;
    struct Circle *next;
};

int main() 
{
    int n;
    scanf("%d", &n);
    struct Circle a[120];
    
    for(int i = 0; i < n; i++) {
        scanf("%d%d", &a[i].pos, &a[i].len);
        if(i == 0) {
            a[i].last = &a[n-1];
            a[i].next = &a[i+1];
        } else if(i == n-1) {
            a[i].last = &a[i-1];
            a[i].next = &a[0];
        } else {
            a[i].last = &a[i-1];
            a[i].next = &a[i+1];
        }
    }
    
    int ask;
    struct Circle *current = &a[0];
    while(scanf("%d", &ask) != EOF && ask != -1) {
        struct Circle *start = current;
        struct Circle *best = NULL;
        do {
            if(current->len >= ask) {
                if(best == NULL || current->len < best->len) {
                    best = current;
                }
            }
            current = current->next;
        } while(current != start);
        if(best != NULL) {
            if(best->len == ask) {
                (best->last)->next = best->next;
                (best->next)->last = best->last;
                current = best->next;
                n--;
            } else if(best->len > ask) {
				best->len -= ask;
                current = best;
            }
        }
    } 
    
    for(int i = 0; i < n; i++) {
    	printf("%d %d\n", current->pos, current->len);
        current = current->next;
	}
    return 0;
}