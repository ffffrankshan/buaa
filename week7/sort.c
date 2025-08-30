#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

int cnt = 0;

void bubble_sort(int a[], int n) 
{
    for (int i = 0; i < n - 1; i++) {
    	int flag = 0;
        for (int j = 0; j < n - i - 1; j++){
            cnt++;
			if (a[j] > a[j + 1]) {
                int temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
                flag = 1;
            }
        }
        if(!flag) return;
    }
}

void select_sort(int a[], int n) 
{
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            cnt++;
			if (a[j] < a[min_idx]) {
                min_idx = j;
            }
        }
        if (min_idx != i) {
            int temp = a[i];
            a[i] = a[min_idx];
            a[min_idx] = temp;
        }
    }
}

void adjust(int k[], int i, int n)
{
	int j, temp;
    temp = k[i];
    j = 2*i+1;
    while(j < n) {
        if(j < n-1 && k[j] < k[j+1])
            j++;
        cnt++;
        if(temp >= k[j]) {
			break;
		}
        k[(j-1)/2] = k[j];
        j = 2*j+1;
    }
    k[(j-1)/2] = temp;
}
void heapSort(int k[], int n) {
    int i;
    int temp;

    // 初始化堆（从最后一个非叶子节点开始调整）
    for (i = n / 2 - 1; i >= 0; i--)
        adjust(k, i, n);

    // 逐个提取堆顶元素（最大值），并调整堆
    for (i = n - 1; i > 0; i--) {
        // 交换堆顶和当前末尾元素
        temp = k[0];
        k[0] = k[i];
        k[i] = temp;

        // 调整堆（只需调整堆顶）
        adjust(k, 0, i);
    }
}

void merge(int x[], int tmp[], int left, int leftend, int rightend)
{     
    int i = left, j = leftend+1, q = left;
    while(i <= leftend && j <= rightend)
    {
        cnt++;
		if(x[i] <= x[j]) 
            tmp[q++] = x[i++];
        else
            tmp[q++] = x[j++];
    }
    while(i <= leftend)
        tmp[q++] = x[i++];
    while(j <= rightend)
        tmp[q++] = x[j++];
    for(i = left; i <= rightend; i++)
        x[i] = tmp[i];
}
void mergeSort(int x[], int tmp[], int left, int right)
{
    if (left < right)
    {
        int center = (left + right) / 2;
        mergeSort(x, tmp, left, center);
        mergeSort(x, tmp, center + 1, right);
        merge(x, tmp, left, center, right);
    }
}

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}
void quickSort(int k[], int left, int right)
{     
	int i, last;
    if(left < right){
        last = left; 
        for(i = left+1; i <= right; i++) {
        	cnt++;
			if(k[i] < k[left]) swap(&k[++last], &k[i]); 
		}
        swap(&k[left], &k[last]);
        quickSort(k, left, last-1); 
        quickSort(k, last+1, right);   
    }
}

int main()
{
	int n, type;
	scanf("%d%d", &n, &type);
	int a[105], tmp[105];
	for(int i = 0; i < n; i++) scanf("%d", &a[i]);
	switch (type)
	{
		case 1:
			select_sort(a, n);
			for(int i = 0; i < n; i++) printf("%d ", a[i]);
			break;
		case 2:
			bubble_sort(a, n);
			for(int i = 0; i < n; i++) printf("%d ", a[i]);
			break;
		case 3:
			heapSort(a, n);
			for(int i = 0; i < n; i++) printf("%d ", a[i]);
			break;
		case 4:
			mergeSort(a, tmp, 0, n-1);
			for(int i = 0; i < n; i++) printf("%d ", a[i]);
			break;
		case 5:
			quickSort(a, 0, n-1);
			for(int i = 0; i < n; i++) printf("%d ", a[i]);
			break;
		default:
			break;
	}
	printf("\n%d", cnt);
    return 0;
}
