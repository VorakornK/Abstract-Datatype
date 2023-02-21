#include<stdio.h>

void swap(int *arr, int i, int  j) {
    int tmp = arr[i];
    arr[i] = arr[j];
    arr[j] = tmp;
} 

void print(int *arr, int n) {
    for (int i = 0; i < n; i++) printf("%d ", arr[i]);
    printf("\n");
}

int main() {
    int n, i, c, at = 1;
    scanf("%d", &n);
    int arr[n];
    for (i=0; i<n; i++) scanf("%d", &arr[i]);
    while (at < n) {
        c = at;
        while (c != 0 && arr[c] < arr[c-1]) {
            swap(arr, c, c-1);
            c--;
            }
        print(arr, n);
        at++;
    }
    return 0;
}