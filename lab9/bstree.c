#include <stdio.h>
#include <stdlib.h>
typedef struct node {
  int data;
  struct node * left;
  struct node * right;
} node_t;
typedef node_t bst_t;
// Write your code here
//
int find_min(bst_t *t) {
    while (t!=NULL) {
        if (t->left==NULL) return t->data;
        t = t->left;
    }
    return -999;
}
int find_max(bst_t *t) {
    while (t!=NULL) {
        if (t->right==NULL) return t->data;
        t = t->right;
    }
    return -999;
}
bst_t *searchNode(bst_t *t, int value) {
    if(t==NULL||t->data == value) return t;
    //printf("%d\n", t->data);
    if(t->data < value) {
        if (t->right!=NULL && t->right->data==value) return t->right;
        else return searchNode(t->right, value);
    }
    else if(t->data > value) {
        if (t->left!=NULL && t->left->data==value) return t->left;
        else return searchNode(t->left, value);
    }
    return NULL;
}
int find(bst_t *t, int value) {
    //printf("%d\n", searchNode(t, value)->data);
    return searchNode(t, value)!=NULL;
}
int ChildChecker(bst_t *t, int value) {
    //none: 0, only left: 1, only right: 2, both: 3
    int state = 0;
    bst_t *parent = searchNode(t, value);
    if(parent->left!=NULL) state += 1;
    if(parent->right!=NULL) state += 2;
    return state;
}
bst_t *searchParent(bst_t *t, int value) {
    if (t!=NULL && t->data == value) return t;
    //printf("%d %d\n", t->data, value);
    if(t->data < value) {
        if (t->right->data==value) return t;
        else return searchParent(t->right, value);
    }
    else if(t->data > value) {
        if (t->left->data==value) return t;
        else return searchParent(t->left, value);
    }
    return NULL;
}
bst_t *insert(bst_t *t, int value) {
    bst_t *new = (bst_t*)malloc(sizeof(bst_t));
    new->data = value;
    if(t == NULL) return new;
    if(t->data < value) {
        if (t->right==NULL) t->right = new;
        else insert(t->right, value);
    }
    else if(t->data > value) {
        if (t->left==NULL) t->left = new;
        else insert(t->left, value);
    }
    return t;
}

void treeprint(bst_t *t,int height) {
    if (t!=NULL) {
        for (int i=0;i<height;i++) {
            printf("     ");
        }
        printf("%d\n", t->data);
        treeprint(t->left,height+1);
        treeprint(t->right,height+1);
    }
}

bst_t *delete(bst_t *t, int value) {
    bst_t *del = searchNode(t, value);
    bst_t *parent = searchParent(t, value);
    int state_of_child = ChildChecker(t, value);
    //printf("%d\n", del==parent);
    if (state_of_child == 0) {
        //leaf case
        if (parent == del) return NULL;
        else if (parent->right == del) parent->right = NULL;
        else if (parent->left == del) parent->left = NULL;
    }
    else if (state_of_child == 1) {
        //only left
        if (parent == del) return del->left;
        if (parent->right == del) parent->right = del->left;
        else if (parent->left == del) parent->left = del->left;
    }
    else if (state_of_child == 2) {
        //only right
        if (parent == del) return del->right;
        if (parent->right == del) parent->right = del->right;
        else if (parent->left == del) parent->left = del->right;
    }
    else if (state_of_child == 3) {
        //both left and right
        //go to right one step
        bst_t *subtreeR = del->right;
        bst_t *subtreeL = del->left;
        //find a min in right subtree
        int min = find_min(subtreeR);
        bst_t *minNode = searchNode(t, min);
        bst_t *parentminMode = searchParent(t, min);
        //delete previous position of minNode
        t = delete(t, min);
        //change a del data to min data
        del->data = min;
        }
    return t;    
}


int main(void) {
  bst_t * t = NULL;
  int n, i;
  int command, data;
  /*t = insert(t, 50);
  t = insert(t, 8);
  t = insert(t, 61);
  t = insert(t, 1);
  t = insert(t, 35);
  t = insert(t, 87);
  treeprint(t, 0);
  t = delete(t, 50);
  treeprint(t, 0);
  printf("%d\n", find(t, 50));
  t = delete(t, 8);
  treeprint(t, 0);
  //treeprint(t, 0);
  t = delete(t, 61);
  treeprint(t, 0);
  //treeprint(t, 0);
  printf("%d\n", find(t, 8));
  printf("%d\n", find(t, 87));
  printf("%d\n", find(t, 61));
    */
  scanf("%d", &n);
  for(i=0;i<n;i++) {
    scanf("%d", &command);
    switch (command) {
      case 1:
        scanf("%d", &data);
        t = insert(t, data);
        break;
      case 2 :
        scanf("%d", &data);
        t = delete(t, data);
        break;
      case 3 :
        scanf("%d", &data);
        printf("%d\n", find(t ,data));
        break;
      case 4 :
        printf("%d\n", find_min(t));
        break;
      case 5 :
        printf("%d\n", find_max(t));
        break;
        }
    }
    
  return 0;
    
}