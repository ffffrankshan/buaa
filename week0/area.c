#include<stdio.h>
#include<math.h>
#include<ctype.h>
#include<string.h>
#include<stdlib.h>

int min(int a, int b) {
	return a < b ? a : b;
}

int max(int a, int b) {
	return a > b ? a : b;
}

int main()
{
	int ax1, ay1, ax2, ay2, bx1, by1, bx2, by2;
	scanf("%d%d%d%d%d%d%d%d", &ax1, &ay1, &ax2, &ay2, &bx1, &by1, &bx2, &by2);
	int x = min(max(ax1, ax2), max(bx1, bx2)) - max(min(ax1, ax2), min(bx1, bx2));
	int y = min(max(ay1, ay2), max(by1, by2)) - max(min(ay1, ay2), min(by1, by2));
	if(x<=0 || y<=0) printf("0");
	else printf("%d", x*y);
    return 0;
}
