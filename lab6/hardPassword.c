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

int size(stack_t *s) {
    stack_t *current = s;
    int count = 0;
    while (current != NULL) {
        count += 1;
        current = current -> next; 
    }
    return count;
}

char top(stack_t *s) {
    return s->data;
}

stack_t *pop(stack_t *s) {
    if (s == NULL) return s;
    return s->next;
}

int check(char *text) {
    stack_t *s = (stack_t*)malloc(sizeof(stack_t));
    int i,lent = strlen(text),c=0;
    for (i=0;i<lent-1;i++) {
        //printf("%c\n", text[i]);
        if (text[i] == 'x') {
            if (c) return 0;
            c = 1;
        }
        else if (text[i] == 'y') {
            return 0;
        }
        else if (c) {
            if (top(s) != text[i]) return 0;
            s = pop(s);
        }
        else if(!c) {
            push(&s, text[i]);
        };
    }
    if (!c) return 0;
    //if (size(s) != 0) return 0;
    return 1;
}

void main() {
    char *text = (char*)malloc(sizeof(char) * 1000000);
    scanf("%s", text);
    printf("%d\n", check(text));
    free(text);
}


