#include<stdio.h>
#include<math.h>
#include<ctype.h>
#include<string.h>
#include<stdlib.h>

struct line {
	int x1;
	int x2;
	int y1;
	int y2;
};

int temp = 1;
void link(struct line l, struct line arr[], int n) {
	for(int i = 0; i < n; i++) {
		if(l.x2 == arr[i].x1 && l.y2 == arr[i].y1) {
			temp++;
			link(arr[i], arr, n);
		}
	}
}

int main()
{
	int n;
	scanf("%d", &n);
	struct line a[105];
	for(int i = 0; i < n; i++) {
		scanf("%d%d%d%d", &a[i].x1, &a[i].y1, &a[i].x2, &a[i].y2);
	}
	int num = 0;
	struct line *ans = NULL;
	for(int i = 0; i < n; i++) {
		temp = 1;
		link(a[i], a, n);
		if(temp > num) {
			num = temp;
			ans = &a[i];
		}
	}
	printf("%d %d %d", num, ans->x1, ans->y1);
    return 0;
}
