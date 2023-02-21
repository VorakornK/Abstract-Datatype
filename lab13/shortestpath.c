#include<stdio.h>
#include<stdlib.h>

int **init_2Darray(int n, int m);
void add(int **arr, int posi, int value);
void add_all(int **arr, int **arr2, int u, int v, int w);
void print(int **arr, int volume);
int is_IN(int *arr, int n, int value);
int *copyarr(int *arr, int n);
void pri(int *arr, int n);
int Spath(int **adja, int **wei, int start, int end, int distance, int *alreIn, int n, int r);
 void Shortest_Path(int **adja, int **wei, int start, int end, int distance, int n);

int main() {
    int i, n, m, p, u, v, w, s, t;
    scanf("%d %d %d", &n, &m, &p);
    int **adjacent  = init_2Darray(n, m);
    int **weight = init_2Darray(n, m); 
    for (i = 0; i < m; i++) {
        scanf("%d %d %d", &u, &v, &w);
        add_all(adjacent, weight, u, v, w);
    }
    for (i = 0; i < p; i++) {
        scanf("%d %d", &s, &t);
        Shortest_Path(adjacent, weight, s, t, 0, n);
    }
    return 0;
}


void add(int **arr, int posi, int value) {
  arr[posi][arr[posi][0]] = value;
  arr[posi][0]++;
}

void add_all(int **arr, int **arr2, int u, int v, int w) {
    add(arr, u, v);
    add(arr, v, u);
    add(arr2, u, w);
    add(arr2, v, w);
}

void print(int **arr, int volume) {
  int i, j;
  for (i=0;i<volume;i++) {
    printf("i = %d have : ", i);
    for (j=1;j<arr[i][0];j++){
      printf("%d ", arr[i][j]);
    }
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

int Spath(int **adja, int **wei, int start, int end, int distance, int *alreIn, int n, int r) {
    if (start == end) return distance;
    int i, sp = -1, cu, *cpy;
    alreIn[n] = start;
    n++;
    for (i=1;i<adja[start][0];i++) {
        if (!is_IN(alreIn, n, adja[start][i])) {
            cpy = copyarr(alreIn, r);
            cu = Spath(adja, wei, adja[start][i], end,distance + wei[start][i], cpy, n, r);
            if ((cu < sp || sp == -1) && cu != -1) sp = cu;
        }
    }
    return sp;
 }

 void Shortest_Path(int **adja, int **wei, int start, int end, int distance, int n) {
    int i, *alreIn = (int *)malloc(sizeof(int) * n);
    for (i=0;i<n+1;i++) alreIn[i] = -1;
    printf("%d\n",Spath(adja, wei, start, end, 0, alreIn, 0, n));
 }