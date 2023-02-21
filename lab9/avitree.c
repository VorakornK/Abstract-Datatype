#include <stdio.h>
#include <stdlib.h>
#include "week9.h"

/*
#ifndef _avl_tree_
typedef struct node {
  int data;
  int height;  
  struct node * left;
  struct node * right;
} node_t;
typedef node_t avl_t;
#endif
*/

// Write your code here
// ** Note that the print_tree() function
// has been implemented already and
// included in the week9.h header
//

int find_min(avl_t *t) {
    while (t!=NULL) {
        if (t->left==NULL) return t->data;
        t = t->left;
    }
    return -999;
}

int height(avl_t *t) {
    if (t == NULL) return -1;
    int h1 = height(t->left);
    int h2 = height(t->right);
    return (h1>h2)? h1+1: h2+1;
}

int balance(avl_t *t) {
  return height(t->left) == height(t->right) || height(t->left)-1 == height(t->right) || height(t->left) == height(t->right)-1;
}

avl_t *searchNode(avl_t *t, int value) {
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

avl_t *searchParent(avl_t *t, int value) {
    if (t != NULL && t->data == value) return t;
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

avl_t *insert(avl_t *t, int value) {
  //Normally insert
  avl_t *newNode = (avl_t*)malloc(sizeof(avl_t));
  newNode->data = value;
  newNode->height = 0;
  if (t == NULL) return newNode;
  else {
    if (t->data > value) {
      if (t->left == NULL) t->left = newNode;
      else t->left = insert(t->left, value);
    }
    else if (t->data < value)  {
      if (t->right == NULL) t->right = newNode;
      else t->right = insert(t->right, value);
    }
  }
  //balance check and adjust
  avl_t *parent = searchParent(t, value);
  avl_t *child = searchNode(t, value);
  avl_t *grandchild = NULL;
  if (balance(t)) {
    //if balance set new height to each node in path
    while (1) {
      parent->height = height(parent);
      //printf("%d\n", parent->data);
      if (parent == t) break;
      parent = searchParent(t, parent->data);
      }
  }
  else {
    //if unbalance 
    //search for a start of unbalance
    while (balance(parent))
    {
      //check next parent(a) and child(b)
      grandchild = child;
      child = parent;
      parent = searchParent(t, parent->data);
    }
    //now parent is First unbalance tree
    //point at parent
    //left rotation
    if (parent->right == child && child->right == grandchild) {
      avl_t *tmp = child->left;
      child->left = parent;
      parent->right = tmp;
      parent->height--;
      t = child;
    }
    //right rotation
    else if (parent->left == child && child->left == grandchild) {
      avl_t *tmp = child->right;
      child->right = parent;
      parent->left = tmp;
      parent->height--;
      t = child;
    }
    //left-right rotation
    else if (parent->left == child && child->right == grandchild) {
      //left rotation
      avl_t *tmp = grandchild->left;
      grandchild->left = child;
      child->right = tmp;
      child->height--;
      parent->left = grandchild;
      //right rotation
      avl_t *tmp2 = grandchild->right;
      grandchild->right = parent;
      parent->left = tmp2;
      parent->height--;
      t = grandchild;
    }
    //right-left rotation
    else if (parent->right == child && child->left == grandchild) {
      //right rotation
      avl_t *tmp =grandchild->right;
      grandchild->right = child;
      child->left = tmp;
      child->height--;
      parent->right = grandchild;
      //left rotation
      avl_t *tmp2 = grandchild->left;
      grandchild->left = parent;
      parent->right = tmp2;
      parent->height--;
      t = grandchild;
    }
    //printf("Unbalance :\n");
    //treeprint(t, 0);
  }
  return t;
}

int ChildChecker(avl_t *t, int value) {
  //none: 0, only left: 1, only right: 2, both: 3
  int state = 0;
  avl_t *parent = searchNode(t, value);
  if(parent->left!=NULL) state += 1;
  if(parent->right!=NULL) state += 2;
  return state;
}

int RotationState(avl_t *t) {
  //0 left 1 right 2 left-right 3 right-left
  if (height(t->right)-height(t->left) == 2) {
    //left case
    if (height(t->right->right)-height(t->right->left) == 1) return 0;
    //right-left case
    else if (height(t->right->left)-height(t->right->right) == 1) return 3;
  }
  else if (height(t->left)-height(t->right) == 2) {
    //right case
    if (height(t->left->left)-height(t->left->right) == 1) return 1;
    //left-right case
    else if (height(t->left->right)-height(t->left->left) == 1) return 2;
  }
  return -1;
}

avl_t *delete(avl_t *t, int value) {
  //normally delete
  avl_t *del = searchNode(t, value);
  avl_t *parent = searchParent(t, value);
  int state_of_child = ChildChecker(t, value);
  if (state_of_child == 0) {
    //leaf case
    if (parent == del) t = NULL;
    else if (parent->right == del) parent->right = NULL;
    else if (parent->left == del) parent->left = NULL;
  }
  else if (state_of_child == 1) {
    //only left
    if (parent == del) t = del->left;
    else if (parent->right == del) parent->right = del->left;
    else if (parent->left == del) parent->left = del->left;
  }
  else if (state_of_child == 2) {
    //only right
    if (parent == del) t = del->right;
    else if (parent->right == del) parent->right = del->right;
    else if (parent->left == del) parent->left = del->right;
  }
  else if (state_of_child == 3) {
    //both left and right
    //go to right one step
    avl_t *subtreeR = del->right;
    avl_t *subtreeL = del->left;
    //find a min in right subtree
    int min = find_min(subtreeR);
    avl_t *minNode = searchNode(t, min);
    avl_t *parentminMode = searchParent(t, min);
    //delete previous position of minNode
    t = delete(t, min);
    //change a del data to min data
    del->data = min;
  }
  //balance checking
  while (1) {
    //printf("Parent : %d\n", parent->data);
    if (!balance(parent)) {
      int state = RotationState(parent);
      //0 left 1 right 2 left-right 3 right-left
      if (state == 0 || state == 1) {
        avl_t *grandparent = searchParent(t, parent->data);
        int x = (grandparent == parent)? 1 : 0;
        int y = 0;
        if (!x) y = (grandparent->left == parent)? 1 : 2; 
        if (state == 0) {
          avl_t *child = parent->right;
          avl_t *tmp = child->left;
          child->left = parent;
          parent->right = tmp;
          parent->height--;
          if (x) t = child;
          else {
            if (y == 1) grandparent->left = child;
            else if (y == 2) grandparent->right = child;
          }
        }
        else if (state == 1) {
          avl_t *child = parent->left;
          avl_t *tmp = child->right;
          child->right = parent;
          parent->left = tmp;
          parent->height--;
            if (x) t = child;
          else {
            if (y == 1) grandparent->left = child;
            else if (y == 2) grandparent->right = child;
          }
        }
        
      }
      else if (state == 2 || state == 3) {
        avl_t *grandparent = searchParent(t, parent->data);
        int x = (grandparent == parent)? 1 : 0;
        int y = 0;
        if (!x) y = (grandparent->left == parent)? 1 : 2; 
        if (state == 2) {
          avl_t *child = parent->left;
          avl_t *grandchild = child->right;
          avl_t *tmp = grandchild->left;
          grandchild->left = child;
          child->right = tmp;
          child->height--;
          parent->left = grandchild;
          avl_t *tmp2 = grandchild->right;
          grandchild->right = parent;
          parent->left = tmp2;
          parent->height--;
          if (x) t = grandchild;
          else {
            if (y == 1) grandparent->left = grandchild;
            else if (y == 2) grandparent->right = grandchild;
        }
        }
        else if (state == 3) {
          avl_t *child = parent->right;
          avl_t *grandchild = child->left;
          avl_t *tmp =grandchild->right;
          grandchild->right = child;
          child->left = tmp;
          child->height--;
          parent->right = grandchild;
          //left rotation
          avl_t *tmp2 = grandchild->left;
          grandchild->left = parent;
          parent->right = tmp2;
          parent->height--;
          if (x) t = grandchild;
          else {
            if (y == 1) grandparent->left = grandchild;
            else if (y == 2) grandparent->right = grandchild;
        }
        }        
      }
      //printf("This one : %d ", parent->data);
      //printf("%d\n", state);
      //print_tree(t);
      }
    if (parent == t) break;
    parent = searchParent(t, parent->data);

  }
  return t;
}



int main(void) {
  avl_t *t = NULL;
  int n , i;
  int command , data;
  t = insert(t, 60);
  t = insert(t, 1);
  t = insert(t, 55);

  t = insert(t, 11);
  t = insert(t, 41);
  t = insert(t, 51);

  t = insert(t, 70);
  t = insert(t, 53);
  t = delete(t, 1);

  t = insert(t, 18);
  t = insert(t, 65);
  t = delete(t, 55);

  t = delete(t, 60);
  t = insert(t, 55);
  t = delete(t, 18);



  /*
  t = insert(t, 21);
  t = insert(t, 8);
  t = insert(t, 34);
  t = insert(t, 3);
  t = insert(t, 16);
  t = insert(t, 26);
  t = insert(t, 42);
  t = insert(t, 2);
  t = insert(t, 5);
  t = insert(t, 11);
  t = insert(t, 18);
  t = insert(t, 23);
  t = insert(t, 31);
  t = insert(t, 37);
  t = insert(t, 47);
  t = insert(t, 1);
  t = insert(t, 4);
  t = insert(t, 6);
  t = insert(t, 9);
  t = insert(t, 13);
  t = insert(t, 17);
  t = insert(t, 19);
  t = insert(t, 22);  
  t = insert(t, 24);
  t = insert(t, 28);
  t = insert(t, 33);
  t = insert(t, 35);
  t = insert(t, 40);
  t = insert(t, 45);
  t = insert(t, 52);
  t = insert(t, 7);
  t = insert(t, 10);
  t = insert(t, 12);
  t = insert(t, 14);
  t = insert(t, 20);
  t = insert(t, 25);
  t = insert(t, 27);
  t = insert(t, 30);
  t = insert(t, 32);  
  t = insert(t, 36);
  t = insert(t, 38);
  t = insert(t, 41);
  t = insert(t, 43);
  t = insert(t, 46);
  t = insert(t, 49);
  t = insert(t, 53);
  t = insert(t, 15);
  t = insert(t, 29);
  t = insert(t, 39);
  t = insert(t, 44);
  t = insert(t, 48);
  t = insert(t, 51);
  t = insert(t, 54);
  t = insert(t, 50);
  print_tree(t);
  printf("Balance : %d\n", balance(t));
  t = delete(t, 1);
  print_tree(t);
  printf("Balance : %d\n", balance(t));
  */
  print_tree(t);
  
  /*scanf("%d", &n);
  for(i=0; i<n; i++) {
    scanf("%d", &command);
    switch(command) {
      case 1 :
        scanf("%d", &data);
        t = insert(t, data);
        break;
      case 2 :
        scanf("%d", &data);
        t = delete(t, data);
        break;
      case 3 :
        print_tree(t);
        break;
    }
  }*/
  return 0;
}