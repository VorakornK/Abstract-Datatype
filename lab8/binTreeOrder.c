#include<stdio.h>
#include<stdlib.h>
#include "week8.h"
//#include <week8.h>

#ifndef __bin_tree__
typedef struct node {
    int data;
    struct node *left;
    struct node *right;
} node_t;
typedef node_t tree_t;
#endif

int preorder(tree_t *t) {
    if (t==NULL) return 0;
    printf("%d ",t->data);
    if (t->left!=NULL) preorder(t->left);
    if (t->right!=NULL) preorder(t->right);
    return 0;
}

void print_preorder(tree_t *t) {
    preorder(t);
    printf("\n");
}

int postorder(tree_t *t) {
    if (t==NULL) return 0;
    if (t->left!=NULL) postorder(t->left);
    if (t->right!=NULL) postorder(t->right);
    printf("%d ",t->data);
    return 0;
}

void print_postorder(tree_t *t) {
    postorder(t);
    printf("\n");
}

int inorder(tree_t *t) {
    if (t==NULL) return 0;
    if (t->left!=NULL) inorder(t->left);
    printf("%d ",t->data);
    if (t->right!=NULL) inorder(t->right);
    return 0;
}

void print_inorder(tree_t *t) {
    inorder(t);
    printf("\n");
}

int main(void) {
    tree_t *t = NULL;
    int n, i;
    int parent, child;
    int branch; // @ root, 1 left, 2 right
    scanf("%d", &n);
    for (i=0; i<n; i++) {
        scanf("%d %d %d", &parent, &child, &branch);
        t = attach(t, parent, child, branch);
    }
    /*t = attach(t, -1, 10, 0);
    t = attach(t, 10, 6, 1);
    t = attach(t, 10, 18, 2);
    t = attach(t, 6, 4, 1);
    t = attach(t, 6, 8, 2);
    t = attach(t, 18, 21, 2);
    t = attach(t, 18, 15, 1);*/
    print_preorder(t);
    print_postorder(t);
    print_inorder(t);
    return 0;
}