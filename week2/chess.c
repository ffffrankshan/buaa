#include<stdio.h>
#include<math.h>
#include<ctype.h>
#include<string.h>
#include<stdlib.h>
int a[20][20];
int main()
{
	for(int i = 1; i <= 19; i++)
		for(int j = 1; j <= 19; j++)
			scanf("%d", &a[i][j]);
			
	for(int i = 1; i <= 19; i++) {
		for(int j = 1; j <= 19; j++) {
			int cnt = 0;
			for(int k = 0; k < 4; k++) {
				if(a[i+k][j]==a[i][j] && a[i][j]!=0) cnt++; 
			}
			if(cnt == 4) {
				if((i==1 && a[i+4][j]==0) || (i==16 && a[i-1][j]==0)) {
					printf("%d:%d,%d\n", a[i][j], i, j);
					return 0;
				}
				if(a[i+4][j]==0 || a[i-1][j]==0) {
					printf("%d:%d,%d\n", a[i][j], i, j);
					return 0;
				}
			}
			cnt = 0;
			for(int k = 0; k < 4; k++) {
				if(a[i][j+k]==a[i][j] && a[i][j]!=0) cnt++; 
			}
			if(cnt == 4) {
				if((j==1 && a[i][j+4]==0) || (j==16 && a[i][j-1]==0)) {
					printf("%d:%d,%d\n", a[i][j], i, j);
					return 0;
				}
				if(a[i][j+4]==0 || a[i][j-1]==0) {
					printf("%d:%d,%d\n", a[i][j], i, j);
					return 0;
				}
			}
			cnt = 0;
			for(int k = 0; k < 4; k++) {
				if(a[i+k][j+k]==a[i][j] && a[i][j]!=0) cnt++; 
			}
			if(cnt == 4) {
				if(((i==1 || j==1) && a[i+4][j+4]==0) || ((i==16 || j==16) && a[i-1][j-1]==0)) {
					printf("%d:%d,%d\n", a[i][j], i, j);
					return 0;
				}
				if(a[i+4][j+4]==0 || a[i-1][j-1]==0) {
					printf("%d:%d,%d\n", a[i][j], i, j);
					return 0;
				}
			}
			cnt = 0;
			for(int k = 0; k < 4; k++) {
				if(a[i+k][j-k]==a[i][j] && a[i][j]!=0) cnt++; 
			}
			if(cnt == 4) {
				if(((i==1 || j==19) && a[i+4][j-4]==0) || ((i==16 || j==4) && a[i-1][j+1]==0)) {
					printf("%d:%d,%d\n", a[i][j], i, j);
					return 0;
				}
				if(a[i+4][j-4]==0 || a[i-1][j+1]==0) {
					printf("%d:%d,%d\n", a[i][j], i, j);
					return 0;
				}
			}
		}
	}
	printf("No\n");
    return 0;
}
