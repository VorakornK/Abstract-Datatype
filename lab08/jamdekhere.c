#include <stdio.h>
#include <stdlib.h>
#include "week8.h"

#ifndef __bin_tree__
typedef struct node {
  int data;
  struct node *left;
  struct node *right; 
} node_t;

typedef node_t tree_t;
#endif

typedef struct nodeA{
    int data;
    struct nodeA *next;
} nodeA_t;

typedef nodeA_t queue_t;

int checkchild(tree_t *t){
  if(t==NULL){
    return 0;
  } else{
    return 1;
  }
}

int check_full(tree_t *t){
  if(t!=NULL){
    return checkchild(t->left)+checkchild(t->right)==2||checkchild(t->left)+checkchild(t->right)==0? 1:0;
  }
  return 1;
}

int is_full(tree_t *t){
  if(t==NULL){
    return 1;
  }
  if(!check_full(t)) return 0;
  if(check_full(t->left)==1&&check_full(t->right)==1){
    return is_full(t->left)==is_full(t->right)? 1:0;
  }
  return 0;
}

int height(tree_t *t){
  if(t==NULL){
    return -1;
  }
  int hl=height(t->left);
  int hr=height(t->right);
  return hl>hr? hl+1:hr+1;
}

int is_perfect(tree_t *t){
  if(t==NULL){
    return 1;
  }
  if(height(t->left)==height(t->right)&&is_full(t)==1){
    return 1;
  }
  return 0;
}

int is_complete(tree_t *t){
  if(t==NULL){
    return 1; 
  }
  if(is_perfect(t->left)==1){
    if(height(t->left)==height(t->right)){
      return is_complete(t->right);
    }
    //is_complete(t->right);
  }
  if(is_perfect(t->right)==1){
    if(height(t->right)+1==height(t->left)){
        return is_complete(t->left);
    }
    //is_complete(t->left);
  } 
  return 0;
}

int is_degenerate(tree_t *t){
  if(t==NULL||(t->left==NULL&&t->right==NULL)){
    return 1;
  }
  if(checkchild(t->left)+checkchild(t->right)==1){
    if(t->left==NULL){
      return is_degenerate(t->right);
    }
    if(t->right==NULL){
      return is_degenerate(t->left);
    } 
  }
  return 0;
}

int checkskewd(tree_t *t,int childside){ //:1=left,2=right
  if(t==NULL||(t->left==NULL&&t->right==NULL)){
    return 1;
  }
  if(childside==1&&t->right==NULL){
    return checkskewd(t->left,1);
  }
  if(childside==2&&t->left==NULL){
    return checkskewd(t->right,2);
  }
  return 0;
}

int is_skewed(tree_t *t){
  if(t->right==NULL){
    return checkskewd(t->left,1);
  }
  else if(t->left==NULL){
    return checkskewd(t->right,2);
  }
  return 0;
}

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

queue_t *dequeue(queue_t *q) {
    if (q == NULL) {
        //printf("Queue is empty.\n");
        return q;
    }
    //printf("%d\n", q->data);
    return q -> next;
}

int is_full2(tree_t *t) {
    // leaf node
    if (t->left == NULL && t->right == NULL) return 1;
    // full node
    if (t->left != NULL && t->right != NULL) {
        if (is_full(t->left) && is_full(t->right)) return 1;
    }
    return 0;
}


int heightH(tree_t *t) {
    if (t == NULL) return 1;
    int h1 = heightH(t->left);
    int h2 = heightH(t->right);
    return (h1>h2)? h1+1: h2+1;
}
int heightL(tree_t *t) {
    if (t == NULL) return 1;
    int h1 = heightL(t->left);
    int h2 = heightL(t->right);
    return (h1<h2)? h1+1: h2+1;
}
//to check that this tree is perfect or not we have to check full and height of the tree
int is_perfect2(tree_t *t) {
    //is tree full
    if(is_full(t) && (heightH(t) == heightL(t))) return 1;
    return 0;
}

tree_t *whoparent(tree_t *t, int data) {
    //printf("%d %d %d\n", t->data, data, t->data == data);
    if (t == NULL)
        return NULL;
    if (t->data == data) {
        return NULL;
    }
    tree_t *result = NULL;
    if (t->left!=NULL) {
        if (t->left->data == data) 
            return t;
        result = whoparent(t->left, data);
        if (result != NULL) return result;
    }
    if (t->right!=NULL) {
        if (t->right->data == data) 
            return t;
        result = whoparent(t->right, data);
        if (result != NULL) return result;
    }
    return NULL;
}

int getheight(tree_t *t, int data){
    if(t == NULL || t->data == data) {              
        return 0;
    }
    int count = 0;
    tree_t *x = whoparent(t, data);
    while (x != NULL) {
        count++;
        x = whoparent(t, x->data);
    }
    return count;
}
//use BFS add to linklisted check void between data
int is_complete2(tree_t *t) {
  int theight = heightH(t);
  queue_t *q = NULL, *check = NULL;
  q = enqueue(q, t->data);
  check = enqueue(check, t->data);
  while (q != NULL) {
    //printf("%d ", q->data);
    //printf("%d\n", check->data);
    tree_t *parent = searchNode(t, q->data);
    q = dequeue(q);
    tree_t *lef = parent->left;
    tree_t *rig = parent->right;
    if (lef != NULL) q = enqueue(q, lef->data);
    if (rig != NULL) q = enqueue(q, rig->data);
    if (!(lef == NULL && rig == NULL) || getheight(t, parent->data) < theight) {
        check = enqueue(check, (lef!=NULL)? lef->data: -999);
        check = enqueue(check, (rig!=NULL)? rig->data: -999);
    }
  }
  //printf("\n");
  int end = 0;
  while (check != NULL) {
    //printf("%d ", check->data);
    if (end && (check->data != -999)) return 0;
    if (check->data == -999) end = 1;
    check = check->next;
  }
  //printf("\n");
  return 1;
}


int is_degenerate2(tree_t *t) {
    if (t->left==NULL&&t->right==NULL) return 1;
    if (t->left!=NULL&&t->right!=NULL) return 0;
    if (t->left!=NULL) return is_degenerate(t->left);
    if (t->right!=NULL) return is_degenerate(t->right);
    return 0;
}

int LCheck(tree_t *t) {
    if (t == NULL) return 1;
    if (t->right!=NULL) return 0;
    return LCheck(t->left);
}
int RCheck(tree_t *t) {
    if (t == NULL) return 1;
    if (t->left!=NULL) return 0;
    return RCheck(t->right);
}

int is_skewed2(tree_t *t) {
    return LCheck(t)||RCheck(t);
}

int main(void){
  tree_t *t=NULL;
  int n, i;
  int parent,child;
  int branch; //0 root, 1 left, 2 right

  /*scanf("%d", &n);
  for (i=0;i<n;i++){
    scanf("%d %d %d", &parent, &child, &branch);
    t = attach(t, parent, child, branch);
  }*/
  t = attach(t, -1, 1, 0);
  t = attach(t, 1, 2, 1);
  t = attach(t, 1, 3, 2);
  t = attach(t, 2, 4, 1);
  t = attach(t, 2, 5, 2);
  t = attach(t, 3, 6, 1);
  t = attach(t, 3, 7, 2);
  printf("%d %d %d %d %d\n",is_full(t)==is_full2(t), is_perfect(t)==is_perfect2(t), is_complete(t)==is_complete2(t), is_degenerate(t)==is_degenerate2(t), is_skewed(t)==is_skewed2(t));

  return 0;
}
/*
7
-1 10 0
10 6 1
10 18 2
6 4 1
6 8 2
18 21 2
18 15 1

5
-1 1 0
1 2 1
1 3 2
2 4 1 
2 5 2

6 
-1 1 0
1 2 1
1 3 2
2 4 1 
2 5 2
3 6 1

4
-1 1 0
1 2 1
2 3 2
3 4 2

3
-1 1 0
1 2 1
2 3 1

7
-1 1 0
1 2 1
1 3 2
2 4 1
2 5 2
5 6 1
5 7 2
*/