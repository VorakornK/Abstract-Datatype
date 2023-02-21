#include<stdio.h>
#include<stdlib.h>

typedef struct node{
    int data;
    struct node *next;
} node_t;

typedef node_t stack2_t;

void push(stack2_t **s, int value) {
    stack2_t *add = (stack2_t*)malloc(sizeof(stack2_t));
    add -> data = value;
    add -> next = NULL;

    add -> next = *s;
    *s = add;
}

int top(stack2_t *s) {
    if (s == NULL) return -1;
    return s->data;
}

stack2_t *pop(stack2_t *s) {
    if (s == NULL) return s;
    return s->next;
}

int find_size(stack2_t *s) {
    stack2_t *current = s;
    int count = 0;
    while (current != NULL) {
        count += 1;
        current = current-> next; 
    }
    return count;
    //printf("%d\n", count);
}

int **init_2Darray(int n);
void add(int **arr, int *size, int posi, int value);
void print(int **arr, int *size, int volume);
int is_IN(int *arr, int n, int value);
int *copyarr(int *arr, int n);
void pri(int *arr, int n);
int *init_array(int n);
int *init_arrayV2(int n);
void Transpose(int **arr, int **arr2, int *size, int *Tsize, int n);
void add_aV2(int *arr, int n, int value);

int cmpfunc (const void * a, const void * b) {
   return ( *(int*)a - *(int*)b );
}



int some_unvisited(int **arr, int *visited, int n) {
    int i;
    for (i=0;i<n;i++) {
        //printf("%d %d\n", visited[i], i);
        if (!is_IN(visited, n, i)) return 1;
    }
    return 0;
}

int get_unvisited(int **arr, int *visited, int n) {
    int i;
    for (i=0;i<n;i++) {
        //printf("%d %d\n", visited[i], i);
        if (!is_IN(visited, n, i)) return i;
    }
    return -1;
}

void clear_arrayV2(int *arr, int n) {
    int i;
    for (i=0;i<n;i++) {
        arr[i] = -1;
    }
}

void printV2(int *arr) {
    int i = 0;
    while (arr[i] != -1) {
        printf("%d ", arr[i]);
        i++;
    }
    printf("\n");
}

int DFS(int **arr, int *size, int n, int start, int *visited, int *visited2, stack2_t **s) {
    printf("%d\n", start);
    add_aV2(visited, n, start);

    int *neighbor = copyarr(arr[start], n);
    int *unvisited_neighbor = init_arrayV2(n);
    int nloop = 0, i;
    for (i=0;i<n;i++) {
        if (neighbor[i] == -1) break;
        if (!is_IN(visited, n, neighbor[i])) {
            add_aV2(unvisited_neighbor, n, neighbor[i]);
            nloop++;
            }
    }
    for (i=0;i<nloop;i++) {
        int *x = copyarr(visited, n);
        DFS(arr, size, n, unvisited_neighbor[i], visited, visited2, s);
    }
    printf("END: %d\n", start);
    push(s, start);
    add_aV2(visited2, n, start);
    return 0;
}

int DFS2(int **arr, int *size, int n, int start, int *visited, stack2_t **s) {
    printf("%d\n", start);
    add_aV2(visited, n, start);
    int *neighbor = copyarr(arr[start], n);
    int *unvisited_neighbor = init_arrayV2(n);
    int nloop = 0, i;
    for (i=0;i<n;i++) {
        if (neighbor[i] == -1) break;
        if (!is_IN(visited, n, neighbor[i])) {
            add_aV2(unvisited_neighbor, n, neighbor[i]);
            nloop++;
        }
    }
    for (i=0;i<nloop;i++) {
        int *x = copyarr(visited, n);
        DFS2(arr, size, n, unvisited_neighbor[i], visited, s);
    }
    push(s, start);
    add_aV2(visited, n, start);
    return 0;
}



void WhatdoIcodehere(int **arr, int *size, int n) {
    int i, j;
    int **Tadjacent  = init_2Darray(n);
    int *Tsize = init_array(n);
    Transpose(arr, Tadjacent, size, Tsize, n);

    int *visited = init_arrayV2(n);
    int *visited2 = init_arrayV2(n);
    int unvisited;
    int t, cc=0;
    stack2_t *s = NULL;
    stack2_t *s2 = NULL;
    DFS(arr, size, n, 0, visited, visited2, &s2);
    while (some_unvisited(arr, visited2, n)) {
        //if (cc>5) break;
        cc++;
        unvisited = get_unvisited(arr, visited2, n);
        printf("unvisited: %d\n", unvisited);
        visited = copyarr(visited2, n);
        DFS(arr, size, n, unvisited, visited, visited2, &s2);
    }
    printf("Start Check\n");
    clear_arrayV2(visited, n);
    clear_arrayV2(visited2, n);
    stack2_t *s3 = s;
    int most = 0, c = 0;
    int **ASSC = init_2Darray(n);
    int *Asize = init_array(n);

    while (top(s) != -1) {
        s2 = NULL;
        t = top(s);
        
        printf("%d\n", top(s));
        s = pop(s);
        DFS(Tadjacent, Tsize, n, t, visited, visited2, &s2);

        if (find_size(s2) > most) most = find_size(s2);
        printf("Size: %d\n", find_size(s2));
        while (top(s2) != -1) {
            add(ASSC, Asize, c, top(s2));
            s2 = pop(s2);
        } 
        c++;
    }
    printf("ADS %d\n", most);
    int *MSSC = init_arrayV2(most);

    for (i=0;i<n;i++) {
        if (Asize[i] == most) {
            for (j=0;j<most;j++) {
                add_aV2(MSSC, most, ASSC[i][j]);
            }
            break;
        }
    }
    qsort(MSSC, most, sizeof(int), cmpfunc);
    for(i=0;i<most;i++) printf("%d ", MSSC[i]);
    printf("\n");

}



int main() {
    int i, n, m, u, v;
    scanf("%d %d", &n, &m);
    int **adjacent  = init_2Darray(n);
    int *size = init_array(n);

    /*add(adjacent, size, 0, 1);
    add(adjacent, size, 1, 2);
    add(adjacent, size, 2, 3);
    add(adjacent, size, 3, 0);
    add(adjacent, size, 2, 4);
    add(adjacent, size, 4, 5);
    add(adjacent, size, 5, 6);
    add(adjacent, size, 6, 4);
    add(adjacent, size, 7, 6);
    add(adjacent, size, 7, 8);*/


    /*add(adjacent, size, 1, 0);
    add(adjacent, size, 2, 1);
    add(adjacent, size, 0, 2);
    add(adjacent, size, 0, 3);
    add(adjacent, size, 3, 4);*/

    for (i = 0; i < m; i++) {
        scanf("%d %d", &u, &v);
        add(adjacent, size, u, v);
    }
    printf("ADAD\n");

    WhatdoIcodehere(adjacent, size, n);
    //print(adjacent, size, n);
    //printf("===Transpose===\n");
    //Transpose(adjacent, Tadjacent, size, Tsize, n);
    //print(Tadjacent, Tsize, n);
    return 0;
}


void Transpose(int **arr, int **arr2, int *size, int *Tsize, int n) {
    int i, j;
    for (i=0;i<n;i++) {
        for (j=0;j<size[i];j++) {
            add(arr2, Tsize, arr[i][j], i);
        }
    }
}

void add(int **arr, int *size, int posi, int value) {
  arr[posi][size[posi]] = value;
  size[posi]++;
}
 

void print(int **arr, int *size, int volume) {
  int i, j;
  for (i=0;i<volume;i++) {
    printf("i = %d have : ", i);
    for (j=0;j<size[i];j++){
      printf("%d ", arr[i][j]);
    }
    printf("\n");
  }
}

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

void add_aV2(int *arr, int n, int value) {
    int i;
    for (i=0;i<n;i++) {
        if (arr[i] == -1) {
            arr[i] = value;
            break; 
        }
    }
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

/*
5 5
1 0
2 1
0 2
0 3
3 4

8 9
0 1
1 2
2 3
2 4
3 0
4 5
5 6
6 4
6 7

0 1
1 2
1 3
1 4
2 5
4 1
4 5
4 6
5 7
5 2
6 7
6 9
7 10
8 6
9 8
10 11
11 9

4 5
0 1
1 2
2 0
2 3
0 3

10 14
0 1
0 4
2 0
2 9
3 2
5 3
5 7
6 1
6 7
7 8
7 0
8 4
8 6
9 5
*/



