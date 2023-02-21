#include<stdio.h>
#include<stdlib.h>
#include<string.h>
void print(int *x) {
    for (int i=1;i<8+1;i++) {
        printf("%d ", x[i]);
    }
    printf("\n");
}

void swap(int *x, int i) {
    //printf("Swap @i : %d\n", i);
    int tmp = x[i];
    x[i] = x[i/2];
    x[i/2] = tmp; 
}

int main() {
    
    char arr[10];
    char arr2[10];
    strcpy(arr, "Phoom");
    strcpy(arr2, arr); 
    strcat(arr, "Kon");  
    strcat(arr2, "Kond");  
    printf("%s\n%s\n", arr, arr2);
    return 0;
}