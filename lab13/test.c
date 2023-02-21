#include <stdio.h>
#include <stdlib.h>


int count_least(int *size, int n) {
    int i, csize, lowest = 99999999, count = 0;
    for (i=0;i<n;i++) {
        csize = size[i];
        if (csize < 1) continue;
        if (lowest > csize) {
            count = 1;
            lowest = csize;
        }
        else if (lowest == csize) count++;
    }
    return count;
}

int main() {
    int a1[] = {3,1,3,2,1};
    int a2[] = {3,1,3,2,1};
    int a3[] = {3,1,3,2,1};
    int a4[] = {3,1,3,2,1};
    int a5[] = {3,1,3,2,1};
    int *s = a;
    printf("least: %d\n", count_least(s, 5));
}

