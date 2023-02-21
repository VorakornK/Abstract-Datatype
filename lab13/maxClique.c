#include<stdio.h>
#include<stdlib.h>

int **init_2Darray(int n, int m);
void add(int **arr, int posi, int value);
void add_all(int **arr, int u, int v);
void print(int **arr, int volume);
int is_IN(int *arr, int n, int value);
int *copyarr(int *arr, int n);
void pri(int *arr, int n);
int *find_least_array(int **arr, int n);
void delete(int **arr, int posi, int n);
int count_clique(int **arr, int n, int posi);
int realcount(int **arr, int n);
int MaxClique(int **arr, int n);

int main() {
    int i, n, m, u, v, s, t;
    scanf("%d %d", &n, &m);
    int **adjacent  = init_2Darray(n, m);
    for (i = 0; i < m; i++) {
        scanf("%d %d", &u, &v);
        add_all(adjacent, u, v);
    }
    
    /*add_all(adjacent, 1, 2);
    add_all(adjacent, 2, 0);
    add_all(adjacent, 0, 1);
    add_all(adjacent, 0, 3);
    add_all(adjacent, 3, 4);*/

    /*add_all(adjacent, 0, 1);
    add_all(adjacent, 0, 3);
    add_all(adjacent, 0, 2);
    add_all(adjacent, 1, 3);
    add_all(adjacent, 1, 2);
    add_all(adjacent, 2, 3);
    add_all(adjacent, 3, 4);
    add_all(adjacent, 2, 4);*/

    /*add_all(adjacent, 0, 1);
    add_all(adjacent, 0, 2);
    add_all(adjacent, 0, 3);
    add_all(adjacent, 1, 3);    
    add_all(adjacent, 2, 4);
    add_all(adjacent, 2, 5);
    add_all(adjacent, 2, 6);
    add_all(adjacent, 3, 4);    
    add_all(adjacent, 3, 5);
    add_all(adjacent, 4, 5);
    add_all(adjacent, 4, 6);
    add_all(adjacent, 5, 6);*/

    /*add_all(adjacent, 8, 0);
    add_all(adjacent, 9, 8);
    add_all(adjacent, 3, 9);
    add_all(adjacent, 0, 3);    
    add_all(adjacent, 3, 4);
    add_all(adjacent, 2, 4);
    add_all(adjacent, 1, 0);
    add_all(adjacent, 1, 2);    
    add_all(adjacent, 5, 6);
    add_all(adjacent, 6, 7);
    add_all(adjacent, 2, 5);
    add_all(adjacent, 5, 7);    
    add_all(adjacent, 4, 7);
    add_all(adjacent, 1, 3);    
    add_all(adjacent, 4, 0);
    add_all(adjacent, 2, 3);
    add_all(adjacent, 1, 4);
    add_all(adjacent, 0, 2);*/


    /*add_all(adjacent, 0, 1);
    add_all(adjacent, 0, 2);
    add_all(adjacent, 1, 2);
    add_all(adjacent, 1, 3);    
    add_all(adjacent, 1, 4);
    add_all(adjacent, 3, 4);    
    add_all(adjacent, 2, 4);    
    add_all(adjacent, 2, 5);
    add_all(adjacent, 4, 5);*/

    printf("%d\n", MaxClique(adjacent, n));
    return 0;
}


void add(int **arr, int posi, int value) {
  arr[posi][arr[posi][0]] = value;
  arr[posi][0]++;
}

void add_all(int **arr, int u, int v) {
    add(arr, u, v);
    add(arr, v, u);
}

void print(int **arr, int volume) {
  int i, j;
  for (i=0;i<volume;i++) {
    printf("i = %d have : ", i);
    for (j=1;j<arr[i][0];j++){
      printf("%d ", arr[i][j]);
    }
    printf("Count: %d", count_clique(arr, volume, i));
    printf("\n");
  }
}

int **init_2Darray(int n, int m) {
  int i, **x = (int **)malloc(sizeof(int *) * n);
  for (i=0;i<n;i++) {
    x[i] = (int *)malloc(sizeof(int) * (m+1));
    x[i][0] = 1;
  }
  return x;
}


int is_IN(int *arr, int n, int value) {
    int i;
    for (i=0;i<n;i++) {
        if (arr[i] == value) return 1;
    }
    return 0;
}

int *copyarr(int *arr, int n) {
    int i, *x = (int *)malloc(sizeof(int) * n);
    for (i=0;i<n;i++) {
        x[i] = arr[i];
    }
    return x;
}

void pri(int *arr, int n) {
    int i;
    for(i=0;i<n+1;i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int count_clique2(int **arr, int n, int posi) {
    int i, j, count = 0;
    //printf("posi: %d\n", posi);
    for (i=1;i<arr[posi][0];i++) {
        if (is_IN(arr[arr[posi][i]], n, posi)) {
            count++;
        }
    }
    return count;
}

int count_clique(int **arr, int n, int posi) {
    int i, j, count = 0;
    //printf("posi: %d\n", posi);
    for (i=1;i<arr[posi][0];i++) {
        if (is_IN(arr[arr[posi][i]], n, posi)) {
            count++;
            count += count_clique2(arr, n, arr[posi][i]);
        }
    }
    return count;
}

int is_there_only_one_least(int **arr, int n) {
    int i, least = n, check = 0;
    for (i=0;i<n;i++) {
        least = (arr[i][0] < least) ? arr[i][0] : least;
    }
    for (i=0;i<n;i++) {
        if (check && arr[i][0]) return 0;
        if (arr[i][0] == least) check = 1;
    }
    return 1;
}

int *init_arrayV2(int n) {
    int i, *x = (int *)malloc(sizeof(int) * n);
    for (i=0;i<n;i++) x[i] = -1;
    return x;
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

void printV2(int *arr, int n) {
    int i;
    for (i=0;i<n;i++) {
        if (arr[i] == -1) break;
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int *find_least_array(int **arr, int n) {
    int i, c = 99999999, *least = init_arrayV2(n);
    if (is_there_only_one_least(arr, n)) {
        for (i=0;i<n;i++) {
            if (arr[i][0] < c && arr[i][0] != -1) c = arr[i][0];
        }
        //printf("C: %d\n", c);
        for (i=0;i<n;i++) {
            //printf("C: %d arr: %d\n", c, arr[i][0]);
            if (count_clique(arr, n, i) == c && arr[i][0] != -1) add_aV2(least, n, i);
        }
    }
    else {
        for (i=0;i<n;i++) {
            if (arr[i][0] < c && arr[i][0] != -1) c = count_clique(arr, n, i);
            //arr[i][0];
        }
        //printf("C: %d\n", c);
        for (i=0;i<n;i++) {
            //printf("C: %d arr: %d\n", c, arr[i][0]);
            if (count_clique(arr, n, i) == c && arr[i][0] != -1) add_aV2(least, n, i);
        }
    }
    
    //printf("C: %d\n", c);
    return least;
}

void delete(int **arr, int posi, int n) {
    int i, j, k;
    arr[posi][0] = -1;
    for (i=0;i<n;i++) {
        k = 0;
        for (j=1;j<arr[i][0];j++) {
            if (arr[i][j] == posi) {
                k = 1;
            }
            if (k) {
                arr[i][j] = arr[i][j+1];
            }
        }
        if (k) arr[i][0]--;
    }
}

int realcount(int **arr, int n) {
    int i, count = 0;
    for (i=0;i<n;i++) {
        if (arr[i][0] != -1) count++;
    }
    return count;
}

int MaxClique(int **arr, int n) {
    print(arr, n);
    printf("\n");
    int i;
    int *larr = find_least_array(arr, n);
    printV2(larr, n);
    if (realcount(arr, n) == arr[larr[0]][0]) {
        return arr[larr[0]][0];
    }
    delete(arr, larr[0], n);
    return MaxClique(arr, n);
}


/*
5 6
0 1
0 2
1 2
1 3
2 4
3 4
*/