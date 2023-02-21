#include <stdio.h>
#include <stdlib.h>

typedef struct heap {
    int *data;
    int last_index;
} heap_t;
// Write your code here
//
heap_t *init_heap(int m) {
    int *arr = (int *)malloc(sizeof(int) * (m+1));
    heap_t *new = (heap_t *)malloc(sizeof(heap_t));
    new->data = arr;
    new->last_index = 1;
    return new;
}
void bfs(heap_t *maxheap) {
    int *arr = maxheap->data;
    for (int i=1;i<maxheap->last_index;i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}
void swap(heap_t *max_heap, int i) {
    //printf("Swap @i : %d\n", i);
    int tmp = max_heap->data[i];
    max_heap->data[i] = max_heap->data[i/2];
    max_heap->data[i/2] = tmp; 
}
void balance(heap_t *max_heap, int i) {
    while (max_heap->data[i] > max_heap->data[i/2] && i > 1) {
        swap(max_heap, i);
        i/=2;   
    }
}
void insert(heap_t *max_heap, int data) {
    max_heap->data[max_heap->last_index] = data;
    balance(max_heap, max_heap->last_index);
    max_heap->last_index++;
}
void delete_max(heap_t *maxheap) {
    if (maxheap->last_index != 1) {
        maxheap->data[1] = maxheap->data[maxheap->last_index-1];
        maxheap->last_index--;
        int x = 1;
        while (2*x < maxheap->last_index && maxheap->data[x] < maxheap->data[2*x]) {
            if (2*x+1 < maxheap->last_index) {
                if (maxheap->data[2*x] > maxheap->data[2*x+1]) {
                    swap(maxheap, 2*x);
                    x = 2*x;
                }
                else if (maxheap->data[2*x] < maxheap->data[2*x+1]) {
                    swap(maxheap, 2*x+1);
                    x = 2*x+1;
                }
            }
        }
    }
    //printf("lastindex : %d\n", maxheap->last_index);
}
void update_key(heap_t *max_heap, int old, int new) {
    for (int i=0;i<max_heap->last_index;i++) {
        if (max_heap->data[i] == old) {
            max_heap->data[i] = new;
            balance(max_heap, i);
            }
    }
}



int find_max(heap_t *max_heap) {
    if (max_heap->last_index == 1) return -1;
    return max_heap->data[1];
}

int main(void) {
    heap_t *max_heap = NULL;
    int     m , n, i;
    int     command , data;
    int     old_key , new_key;
    scanf("%d %d", &m, &n);
    max_heap = init_heap(m);
    for(i = 0; i < n; i ++) {
        scanf("%d", &command);
        switch(command) {
        case 1 :
            scanf("%d", &data);
            insert(max_heap, data);
            break;
        case 2 :
            delete_max(max_heap);
            //printf("last : %d\n", max_heap->last_index);
            break;
        case 3 :
            printf("%d\n", find_max(max_heap));
            break;
        case 4 :
            scanf("%d %d", &old_key, &new_key);
            update_key(max_heap, old_key, new_key);
            break;
        case 5 :
            bfs(max_heap);
            break;
        }
    }
  return 0;
}

/*
10 8
1 2
1 3
1 5
1 6
5

1 1
1 7
5


10 11
1 2
3 

1 3
1 4
1 5
1 6
3

1 1
3

1 7
3


10 11
1 2
5

1 3
1 4
1 5
1 6
3

2
5

1 7
5


5 13
1 2
1 3
1 4
5

2
5

2
5

2
5

2
5

3


5 10
1 2
1 3
1 4
5

4 2 5
5

4 4 1
5

4 5 10
5


5 13
1 82
1 79
1 66
1 78
5

2
3

1 93
2
1 69
5

1 99
3


5 11
3

1 11
1 3
1 90
1 43
3

2
2
5

4 3 20
3
*/