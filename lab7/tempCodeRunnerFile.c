#include <stdio.h>
#include <stdlib.h>


typedef struct node {
    int value;
    struct node *first_child;
    struct node *next_sibling;
    struct node *prev_node;
} node_t;
typedef node_t tree_t;

typedef struct nodes{
    int data;
    struct nodes *next;
} nodeX_t;

typedef nodeX_t stack_t;

typedef struct nodeA{
    int data;
    struct nodeA *next;
} nodeA_t;

typedef nodeA_t queue_t;

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

stack_t *push(stack_t **s, int value) {
    stack_t *add = (stack_t*)malloc(sizeof(stack_t));
    add -> data = value;
    add -> next = NULL;

    add -> next = *s;
    *s = add;
}

int top(stack_t *s) {
  if (s != NULL) return s->data;
    /*if (s == NULL) printf("Stack is empty.\n");
    else printf("%d\n", s->data)*/
}

stack_t *pop(stack_t *s) {
    if (s == NULL) return s;
    return s->next;
}

tree_t *basicsearch(tree_t *t, int v) {
    if (t == NULL || t -> value == v) return t;
    tree_t *pos = basicsearch(t->first_child, v);
    if (pos != NULL) return pos;
    else return basicsearch(t->next_sibling, v);
}


int search(tree_t *t, int v) {
    if (basicsearch(t, v) == 0) return 0;
    return 1;
}

tree_t *attach(tree_t *t, int parent, int child) {
    tree_t *node = (tree_t *)malloc(sizeof(tree_t));
    node->value = child;
    node->first_child = NULL;
    node->next_sibling = NULL;
    node->prev_node = NULL;

    tree_t *pos = basicsearch(t, parent);
    if (pos == NULL) return node;
    else {
        if (pos->first_child == NULL) {
            node->prev_node = pos;
            pos->first_child = node;
            }
        else {
            pos = pos->first_child;
            while(pos->next_sibling != NULL) {
                pos = pos->next_sibling;
                }
            node->prev_node = pos;
            pos->next_sibling = node;
        }
    }
    return t;
}

tree_t *detach(tree_t *t, int node) {
    if (t == NULL) return t;
    if (t->value == node) return t->prev_node;
    tree_t *pos = basicsearch(t, node);
    if (pos == NULL) return t;
    tree_t *before = pos->prev_node;
    tree_t *after = pos->next_sibling;
    if (before->first_child == pos) {
      if (after != NULL) after->prev_node = before;
      before->first_child = after;
    }
    else if (before->next_sibling == pos) {
      after->prev_node = before;
      before->next_sibling = after;
      }
    free(pos);
    return t;
}

int degree(tree_t *t, int node) {
  //if (t == NULL) return ;
  tree_t *pos = basicsearch(t, node);
  if (pos == NULL) return 0;
  int count = 0;
  if (pos->first_child != NULL) {
    pos = pos->first_child;
    while (pos != NULL) {
      pos = pos->next_sibling;
      count++;
    }
  }
  return count;
}

int is_root(tree_t *t, int node) {
  if (t==NULL) return 0;
  return t->value == node; 
}

int is_leaf(tree_t *t, int node) {
  if (t==NULL) return 0;
  tree_t *pos = basicsearch(t, node);
  if (pos == NULL) return 0; 
  if (pos->first_child == NULL) return 1;
  return 0;
}

int siblings(tree_t *t, int node) {
  if (t!=NULL) {
    tree_t *pos = basicsearch(t, node);
    if (pos == NULL) {
      //printf("\n");
      return 0;
      } 
    tree_t *prev = pos;
    if (pos != t) { 
      while (prev->prev_node->first_child != prev) {
        prev = prev->prev_node;
        }
      while (prev != NULL) {
        if (prev != pos) printf("%d ", prev->value);
        prev = prev->next_sibling;
      }
    }
  }
  printf("\n");
}

int depth(tree_t *t, int node) {
  //if (t==NULL) return 0;
  tree_t *pos = basicsearch(t, node);
  if (pos == NULL) return 0; 
  tree_t *prev = pos;
  int count = 0;
  while (prev == NULL || prev->prev_node != NULL) {
    if (prev->prev_node != NULL && prev->prev_node->first_child == prev) count++;
    prev = prev->prev_node;
    }
  return count;
}

tree_t *Whoisyourfather(tree_t *t, int x) {
  tree_t *current = basicsearch(t, x);
  if (current == t) return t;
  while(current->prev_node->first_child != current) {
    current = current->prev_node;
  }
  return current->prev_node;
}

int print_path(tree_t *t, int start, int end) {
  stack_t *x = NULL;
  tree_t *current = basicsearch(t, end);
  tree_t *sta = basicsearch(t, start);
  if (current == NULL || sta == NULL) {
    //printf("\n");
    return 0;
  } 
  while (current != sta) {
    push(&x, current->value);
    current = Whoisyourfather(t, current->value);
  }
  push(&x, current->value);
  while (x != NULL) {
    printf("%d ", top(x));
    x = pop(x);
  }  
  printf("\n");
}

int path_length(tree_t *t, int start, int end) {
  tree_t *current = basicsearch(t, end);
  tree_t *sta = basicsearch(t, start);
  if (current == NULL) return 0; 
  if (sta == NULL) return 0;
  int count = 1;
  while (current != sta) {
    count++;
    current = Whoisyourfather(t, current->value);
  }
  return count;
}

int ancestor(tree_t *t, int node) {
  stack_t *x = NULL;
  tree_t *current = basicsearch(t, node);
  if (current == NULL) return 0; 
  while (current != t) {
    push(&x, current->value);
    current = Whoisyourfather(t, current->value);
  }
  push(&x, current->value);
  while (x != NULL) {
    printf("%d ", top(x));
    x = pop(x);
  }  
  printf("\n");
}

int dfs(tree_t *t) {
  if (t == NULL) return 0;
  stack_t *x = NULL;
  push(&x, t->value);
  while (x != NULL) {
    tree_t *this = basicsearch(t, top(x));
    x = pop(x);
    printf("%d ", this->value);
    tree_t *child = this->first_child;
    if (child == NULL) continue;
    while (child->next_sibling != NULL) child = child->next_sibling;
    while (child != this) {
      push(&x, child->value);
      child = child->prev_node;
    }
  }
  printf("\n");
}

int bfs(tree_t *t) {
  if (t == NULL) return 0;
  queue_t *q = NULL;
  q = enqueue(q, t->value);
  while (q != NULL) {
    printf("%d ", q->data);
    tree_t *x = basicsearch(t, q->data); 
    q = dequeue(q);
    tree_t *child = x->first_child;
    //if (child == NULL) continue;
    while (child != NULL) {
      q = enqueue(q, child->value);
      child = child->next_sibling;
    }
  }
  printf("\n");
}

int descendant(tree_t *t, int node) {
  if (t == NULL) return 0;
  tree_t *current = basicsearch(t, node);
  if (current == NULL) return 0; 
  bfs(current);
}



int print_tree(tree_t *t) {
  if (t == NULL) return 0;
  stack_t *x = NULL;
  int dep = 0;
  push(&x, t->value);
  while (x != NULL) {
    tree_t *this = basicsearch(t, top(x));
    dep = depth(t, top(x));
    x = pop(x);
    for (int i=0;i<dep;i++) printf("    ");
    printf("%d\n", this->value);
    tree_t *child = this->first_child;
    if (child == NULL) continue;
    while (child->next_sibling != NULL) child = child->next_sibling;
    while (child != this) {
      push(&x, child->value);
      child = child->prev_node;
    }
  }
}


int main(void) {
  tree_t *t = NULL;
  int n, i, command;
  int parent, child, node, start, end;

  scanf("%d", &n);
  for (i=0; i<n; i++) {
    scanf("%d", &command);
    switch(command) {
      case 1:
        scanf("%d %d", &parent, &child);
        t = attach(t, parent, child);
        break;
      case 2:
        scanf("%d", &node);
        t = detach(t, node);
        break;
      case 3:
        scanf("%d", &node);
        printf("%d\n", search(t, node));
        break;
      case 4:
        scanf("%d", &node);
        printf("%d\n", degree(t, node));
        break;
      case 5:
        scanf("%d", &node);
        printf("%d\n", is_root(t, node));
        break;
      case 6:
        scanf("%d", &node);
        printf("%d\n", is_leaf(t, node));
        break;
      case 7:
        scanf("%d", &node);
        siblings(t, node);
        break;
      case 8:
        scanf("%d", &node);
        printf("%d\n", depth(t, node));
        break;
      case 9:
        scanf("%d %d", &start, &end);
        print_path(t, start, end);
        break;
      case 10:
        scanf("%d %d", &start, &end);
        printf("%d\n", path_length(t, start, end));
        break;
      case 11:
        scanf("%d", &node);
        ancestor(t, node);
        break;
      case 12:
        scanf("%d", &node);
        descendant(t, node);
        break;
      case 13:
        bfs(t);
        break;
      case 14:
        dfs(t);
        break;
      case 15:
        print_tree(t);
        break;
    }
  }
  return 0;
}