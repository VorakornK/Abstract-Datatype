#include<stdio.h>
#include<stdlib.h>

typedef struct node{
    char data;
    struct node *next;
} node_t;

typedef node_t stack_t;

stack_t *push(stack_t *s, char value) {
    stack_t *add = (stack_t*)malloc(sizeof(stack_t));
    add -> data = value;
    add -> next = NULL;

    add -> next = s;
    s = add;
    return s;
}

void size(stack_t *s) {
    stack_t *current = s;
    int count = 0;
    while (current != NULL) {
        count += 1;
        current = current -> next; 
    }
    printf("%d\n", count);
}

stack_t *pop(stack_t *s) {
    if (s == NULL) return s;
    return s->next;
}

char top(stack_t *s) {
    if (s != NULL) return s->data;
}

int check(stack_t *s) {
    int i, n;
    scanf("%d", &n);
    char *text = (char *)malloc(sizeof(char) * n);
    scanf("%s", text);
    for (i=0;i<n;i++) {
        if (text[i] == *"[" || text[i] == *"(" || text[i] == *"{") s = push(s, text[i]);
        else {
            if (text[i] == *"]") {
                if (top(s) != *"[") return 0;
                s = pop(s);
            } 
            else if (text[i] == *")") {
                if (top(s) != *"(") return 0;
                s = pop(s);
            }
            else if (text[i] == *"}") {
                if (top(s) != *"{") return 0;
                s = pop(s);
            }
        }
    }
    return 1;
}

int main() {
    stack_t *s = NULL;
    printf("%d\n", check(s));
    return 0;
}