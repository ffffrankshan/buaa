#include <stdio.h>

// 检查元素是否已经被使用
int isUsed(int arr[], int start, int end, int value) {
    for (int i = start; i <= end; i++) {
        if (arr[i] == value) {
            return 1;
        }
    }
    return 0;
}

void permute(int arr[], int result[], int start, int end) {
    if (start > end) {
        for (int i = 0; i <= end; i++) {
            printf("%d ", result[i]);
        }
        printf("\n");
        return;
    }

    for (int i = 0; i <= end; i++) {
        if (!isUsed(result, 0, start - 1, arr[i])) {
            result[start] = arr[i];
            permute(arr, result, start + 1, end);
        }
    }
}

int main() {
    int n;
    scanf("%d", &n);
    int arr[n];
    for (int i = 0; i < n; i++) {
        arr[i] = i + 1;
    }

    int result[n];
    permute(arr, result, 0, n - 1);

    return 0;
}