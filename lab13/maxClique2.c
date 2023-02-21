#include<stdio.h>
#include<stdlib.h>

int **init_2Darray(int n);
int *init_array(int n);
int *init_arrayV2(int n);
void add(int **arr, int *size, int posi, int value);
void add_aV2(int *arr, int n, int value);

int count_degree(int *size, int posi) {
    return size[posi] - 1;
}

void removeNode(int **arr, int *size, int n, int remove) {
    int i, j, alfind;
    for (i=0;i<n;i++) {
        alfind = 0;
        for (j=0;j<size[i];j++) {
            if (i == remove) a[i][j] = -1;
            else {
                if (arr[i][j] == remove) alfind = 1;
                if (alfind) {
                    if (j == size[i] -1) arr[i][j] = -1;
                    else arr[i][j] = arr[i][j+1];
                } 
            }
        }
        if (alfind) size[i]--;
    }
    size[remove] = 0;
}

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

void MaxClique(int **arr, int * size, int n) {

}



int main() {
    int i, n, m, u, v, s, t;
    scanf("%d %d", &n, &m);
    int **adjacent  = init_2Darray(n, m);
    int *size = init_array(n)
    for (i = 0; i < m; i++) {
        scanf("%d %d", &u, &v);
        add_all(adjacent, u, v);
    }
    printf("%d\n", MaxClique(adjacent, size, n));
    return 0;
}

/*
5 5
1 2
2 0
0 1
0 3
3 4
//3

5 8
0 1
0 3
0 2
1 3
1 2
2 3
3 4
2 4
//4

ึ7 12
0 1
0 2
0 3
1 3
2 4
2 5
2 6
3 4
3 5
4 5
4 6
5 6
//4

10 18
8 0
9 8
3 9
0 3
3 4
2 4
1 0
1 2
5 6
6 7
2 5
5 7
4 7
1 3
4 0
2 3
1 4
0 2
//5

6 9
0 1
0 2
1 2
1 3
1 4
3 4
2 4
2 5
4 5
//3

5 6
0 1
0 2
1 2
1 3
2 4
3 4
//3

*/

int **init_2Darray(int n) {
  int i, j, **x = (int **)malloc(sizeof(int *) * n);
  for (i=0;i<n;i++) {
    x[i] = (int *)malloc(sizeof(int) * n);
    for (j=0;j<n;j++) x[i][j] = -1;
  }

  return x;
}

int *init_array(int n) {
    int i, *x = NULL;
    x = (int *)malloc(sizeof(int) * n);
    return x;
}

int *init_arrayV2(int n) {
    int i, *x = (int *)malloc(sizeof(int) * n);
    for (i=0;i<n;i++) x[i] = -1;
    return x;
}

void add(int **arr, int *size, int posi, int value) {
  arr[posi][size[posi]] = value;
  size[posi]++;
}


void add_aV2(int *arr, int n, int value) {
    int i;
    for (i=0;i<n;i++) {
        if (arr[i] == -1) {
            arr[i] = value;
            break; 
        }
    }
}