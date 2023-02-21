#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct node{
    double data;
    struct node *next;
} node_t;

typedef node_t stack_t;

stack_t *push(stack_t *s, double value) {
    stack_t *add = (stack_t*)malloc(sizeof(stack_t));
    add -> data = value;
    add -> next = NULL;

    add -> next = s;
    s = add;
    return s;
}

double top(stack_t *s) {
    return s->data;
}
stack_t *pop(stack_t *s) {
    return s->next;
}


int Postfix(int n, char *text) {
    stack_t *pf = (stack_t*)malloc(sizeof(stack_t));
    int i,v,n1 = strlen(text);
    double a = 0, b = 0; 
    for (i=0;i<n1;i++) {
        //top(pf);
        if (text[i] == *"+" || text[i] == *"-" || text[i] == *"*" || text[i] == *"/") {
            a = top(pf);
            pf = pop(pf);
            b = top(pf);
            pf = pop(pf);
            //printf("%f %c %f\n", a, text[i], b);
            if (text[i] == *"+") pf = push(pf, b+a);
            if (text[i] == *"-") pf = push(pf, b-a);
            if (text[i] == *"*") pf = push(pf, b*a);
            if (text[i] == *"/") pf = push(pf, b/a);
        }
        else {
            v = text[i]-'0';
            pf = push(pf, v);
        }
    }
    printf("%.2f\n", top(pf));
}

void main() {
    int n,i;
    scanf("%d", &n);
    char *text = (char *)malloc(sizeof(char) * n);
    scanf("%s", text);
    Postfix(n, text);
}


