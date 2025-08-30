#include<stdio.h>
#include<math.h>
#include<ctype.h>
#include<string.h>
#include<stdlib.h>

typedef struct memoryZone {
    int position;
    int size;
    struct memoryZone *last;
    struct memoryZone *next;
} memoryZone;

void initMemoryZone(memoryZone *zone, int total) {
	zone[0].last = &zone[total-1];
	zone[0].next = &zone[1];
    for(int i = 1; i < total-1; i++) {
        zone[i].last = &zone[i - 1];
        zone[i].next = &zone[i + 1];
    }	
	zone[total-1].last = &zone[total-2];
	zone[total-1].next = &zone[0];
    
}
void allocateMemory(memoryZone **current, int request, int *total) {
    memoryZone *start = *current;
    memoryZone *bestFit = NULL;

    do {
        if ((*current)->size >= request) {
            if (bestFit == NULL) {
                bestFit = *current;
                break;
            }
        }
        *current = (*current)->next;
    } while (*current != start);

    if (bestFit != NULL) {
        if (bestFit->size == request) {
            bestFit->last->next = bestFit->next;
            bestFit->next->last = bestFit->last;
            *current = bestFit->next;
            (*total)--;
        } else {
            bestFit->size -= request;
            *current = bestFit;
        }
    }
}
int main() 
{
    int total;
    memoryZone zone[100];
    scanf("%d", &total);

    for (int i = 0; i < total; i++) {
        scanf("%d %d", &zone[i].position, &zone[i].size);
    }

    initMemoryZone(zone, total);

    int request;
    memoryZone *current = &zone[0];

    while (scanf("%d", &request) != EOF && request != -1) {
        allocateMemory(&current, request, &total);
    }

    for (int i = 0; i < total; i++) {
        printf("%d %d\n", current->position, current->size);
        current = current->next;
    }

    return 0;
}    
