#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct node{
    char data;
    struct node *next;
} node_t;
typedef node_t stack_t;
stack_t *push(stack_t **s, char value) {
    stack_t *add = (stack_t*)malloc(sizeof(stack_t));
    add -> data = value;
    add -> next = NULL;

    add -> next = *s;
    *s = add;
}
char top(stack_t *s) {
    if (s==NULL) return 0;
    return s->data;
}
stack_t *pop(stack_t *s) {
    if (s == NULL) return NULL;
    return s->next;
}
int check3() {
    stack_t *s = NULL;
    char d;
    int c = 0;
    while(1) {
        scanf("%c", &d);
        if (d == 'y' || d == 'x') { 
            if (d == 'y') break;
            else {
                if (c) return 0;
                c = 1;
            }
        }
        else {
            if (!c) push(&s, d);
            else if (c) {
                printf("%c %c ", d, top(s));
                if (top(s) != d) return 0;
                s = pop(s);
                printf("%c\n", top(s));
            } 
        }
    }
    //printf("%c\n", top(s));
    if (s != NULL) return 0;
    return 1;
}

void main() {
    printf("%d\n", check3());
}


