#include <stdio.h>
#include<string.h>

int main() { 
    int a[10][10]={0};
    a[0][6] = 1;
    printf("%d",*((*a+4)+2));
    return 0; 
} 

/*0 1 2 3 4 5 6 7
	*/