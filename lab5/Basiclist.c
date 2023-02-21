#include<stdio.h>
#include<stdlib.h>
typedef struct node {
  int data;
  struct node *next;
} node_t;
node_t *append(node_t *startNode) {
    node_t *anew = (node_t *)malloc(sizeof(node_t));
    int x;
    scanf(" %d", &x);
    anew->data = x;
    anew->next = NULL;
    if (startNode == NULL) {
        return anew;
    }
    else {
        node_t *pointer = startNode;
        while (pointer->next != NULL) {
            pointer = pointer->next;
        }
        pointer->next = anew;
    }    
    return startNode; 
}
void show(node_t *startNode) {
    node_t *current = startNode;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}
void get(node_t *startNode) {
    int i = 0,x;
    node_t *current = startNode;
    scanf(" %d", &x);
    while (1) {
        if (i == x) {
            printf("%d\n", current->data);
            break;
        }
        current = current->next;
        i++;
    }
}
node_t *reverse(node_t *startNode) {
    node_t *current = startNode;
    node_t *front;
    node_t *back;
    while (current != NULL) {
        back = current->next;
        current->next = front;
        front = current;
        current = back;
    }
    return front;
}
node_t *cut(node_t *startNode) {
    node_t *current = startNode;
    node_t *start, *end;
    int st,en,i=0;
    scanf(" %d %d", &st, &en);
    while (1) {
        if (st == i) start = current;
        if (en == i) {
            end = current;
            end->next = NULL;
            return start;
        }
        current = current->next;
        i++;
    }
}
int main(void) {
    node_t *startNode;
    int n,i,add;
    char command;
    startNode = NULL;
    scanf("%d", &n);
    for (i=0;i<n;i++) {
        scanf(" %c", &command);
        switch (command) {
        case 'A':
            startNode = append(startNode);
            break;
        case 'G':
            get(startNode);
            break;
        case 'S':
            show(startNode);
            break;
        case 'R':
            startNode = reverse(startNode);
            break;
        case 'C':
            startNode = cut(startNode);
            break;
        default:
            break;
        }
    }
    return 0;
}