#include<stdio.h>
#include<stdlib.h>

typedef struct node{
    int data;
    struct node *next;
} node_t;

typedef node_t queue_t;

queue_t *enqueue(queue_t *q, int value) {
    queue_t *nqueue = (queue_t *)malloc(sizeof(queue_t));
    nqueue -> data = value;
    nqueue -> next = NULL;
    if (q == NULL) {
        q = nqueue;
        return q;
    }
    queue_t *current = q;
    while (current->next != NULL) { 
        current = current -> next;
    }
    current -> next = nqueue;
    return q;
}

void show(queue_t *q) {
    if (q == NULL) printf("Queue is empty.\n");
    else { 
        queue_t *current = q;
        while (current != NULL) {
            printf("%d ", current->data);
            current = current -> next;
        }
        printf("\n");
    }
}

queue_t *dequeue(queue_t *q) {
    if (q == NULL) {
        printf("Queue is empty.\n");
        return q;
    }
    printf("%d\n", q->data);
    return q -> next;
}

void empty(queue_t *q) {
    if (q == NULL) printf("Queue is empty.\n");
    else printf("Queue is not empty.\n");
}

void size(queue_t *q) {
    int count = 0;
    queue_t *current = q;
    while (current != NULL) {
        count += 1;
        current = current -> next;
    }
    printf("%d\n", count);
}


int main() {
    queue_t *q = NULL;
    int n, i, command, value;
    scanf("%d", &n);
    for (i=0;i<n;i++) {
        scanf("%d", &command);
        switch (command) {
            case 1:
                scanf("%d", &value);
                q = enqueue(q, value);
                break;
            case 2:
                q = dequeue(q);
                break;
            case 3:
                show(q);
                break;
            case 4:
                empty(q);
                break;
            case 5:
                size(q);
                break;
        }
    }
    return 0;
}