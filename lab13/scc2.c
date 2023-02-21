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

void printV2(int *arr, int n) {
    int i;
    for (i=0;i<n;i++) {
        if (arr[i] == -1) break;
        printf("%d ", arr[i]);
    }
    printf("\n");
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
int is_IN(int *arr, int n, int value);
int *init_array(int n);
int *init_arrayV2(int n);
void Transpose(int **arr, int **arr2, int *size, int *Tsize, int n);
void add_aV2(int *arr, int n, int value);

int cmpfunc (const void * a, const void * b) {
   return ( *(int*)a - *(int*)b );
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
    for (i=0;i<n;i++) arr[i] = -1;
}

void DFS(int **arr, int *size, int n, int start, int *visited, stack2_t **s) {
    //printf("@: %d\n", start);
    if (!is_IN(visited, n, start)) add_aV2(visited, n, start);
    //printV2(visited, n);
    int i;
    for (i=0;i<size[start];i++) {
        if (!is_IN(visited, n, arr[start][i])) {
            DFS(arr, size, n, arr[start][i], visited, s);
        }
    }
    push(s, start);
    //printf("END: %d\n", start);
}

void Find_Most_SCC(int **arr, int *size, int n) {
    int *visited = init_arrayV2(n);
    stack2_t *s = NULL;
    DFS(arr, size, n, 0, visited, &s);
    //printf("Size of stack: %d\n", find_size(s));
    //Check if there are some node unvisited
    while (find_size(s) < n) {
        int unvisited;
        unvisited = get_unvisited(arr, visited, n);
        //printf("Unvisited Node: %d\n", unvisited);
        DFS(arr, size, n, unvisited, visited, &s);
    }

    //Run G transpose
    int **Tadjacent  = init_2Darray(n);
    int *Tsize = init_array(n);
    Transpose(arr, Tadjacent, size, Tsize, n);
    clear_arrayV2(visited, n);
    stack2_t *s2 = NULL;
    int most = 0, **ASSC = init_2Darray(n), *Asize = init_array(n), i, j, t, sizeS2, c=0;
    printf("==== Transpose Start Here ====\n");
    while (top(s) != -1) {
        s2 = NULL;
        t = top(s);

        s = pop(s);
        DFS(Tadjacent, Tsize, n, t, visited, &s2);
        sizeS2 = find_size(s2);
        most = (sizeS2 > most)? sizeS2 : most;
        for (i=0;i<sizeS2;i++) {
            add(ASSC, Asize, c, top(s2));
            s2 = pop(s2);
        }
        c++;
    }

    //printf("Most : %d\n", most);
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

    for (i=0;i<most;i++) printf("%d ", MSSC[i]);
    printf("\n");

}

int main() {
    int i, n, m, u, v;
    scanf("%d %d", &n, &m);
    int **adjacent  = init_2Darray(n);
    int *size = init_array(n);
    
    for (i = 0; i < m; i++) {
        scanf("%d %d", &u, &v);
        add(adjacent, size, u, v);
    }
    //DFS(adjacent, size, n, 0, visited, &s);
    Find_Most_SCC(adjacent, size, n);
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

12 17
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

9 10
0 1
1 2
2 3
3 0
2 4
4 5
5 6
6 4
7 6
7 8

10 18
0 1
1 2
2 3
3 4
4 5
5 4
3 5
3 6
3 7
6 5
7 6
2 7
7 2
8 7
1 8
8 0
9 8
0 9
*/