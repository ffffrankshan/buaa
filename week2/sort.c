#include<stdio.h>
#include<math.h>
#include<ctype.h>
#include<string.h>
#include<stdlib.h>

struct book {
	char name[25];
	char phone[15];
};

void sort(struct book a[], int num) {
    struct book temp;
    for(int i = 0; i < num - 1; ++i) {
        for(int j = 0; j < num - 1 - i; ++j) {
            if(strcmp(a[j].name, a[j + 1].name) > 0) {
                temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
            }
        }
    }
}

int main()
{
	int n;
	scanf("%d", &n);
	getchar();
	struct book list[105]; 
	for(int i = 0; i < n; i++) {
		scanf("%s %s", list[i].name, list[i].phone);
	}
	
	for(int i = 0; i < n; ++i) {
        for(int j = i + 1; j < n; ++j) {
            if(strcmp(list[i].name, list[j].name) == 0) {
            	if(strcmp(list[i].phone, list[j].phone) == 0) {
                	for(int k = j; k < n - 1; ++k) {
                    	list[k] = list[k + 1];
                	}
                	n--;
                	j--; 
            	} 
			}  
        }
    }
	for(int i = 0; i < n; i++) {
		int count = 0;
		for(int j = i + 1; j < n; j++) {
			if(strcmp(list[i].name, list[j].name) == 0) {
            	count++;
            	char add[5];
				sprintf(add, "_%d", count);
				strcat(list[j].name, add);
            }
		}
	}
	sort(list, n);
	for(int i = 0; i < n; i++) {
		printf("%s %s\n", list[i].name, list[i].phone);
	}
    return 0;
}
