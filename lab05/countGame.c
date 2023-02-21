#include <stdio.h>

typedef struct Node {
  int name;
  int alcohol;
  struct Node *next;
  struct Node *prev;
} node_t;

node_t *head = NULL;
node_t *tail = NULL;

void show() {
  node_t *current = head;
  do {
    printf("%d %d %d %d\n", current->name, current->alcohol, current->next->name, current->prev->name);
    current = current->next;
  } while (current != head);
}

void Delete(node_t *All, node_t del) {
  //show();
  //printf("\n");
  node_t *current = &del;
  node_t *Next = del.next;
  node_t *Prev = del.prev;
  Next->prev = Prev;
  Prev->next = Next;
  if (del.name == head->name) {
    head = del.next;
    }
  if (del.name == tail->name) {
    tail = del.prev;
    }
  //printf("%d %d\n", prev->name, next->name);
  //show();  
}

int CheckDegit(int count, int k) {
  while (count > 0) {
    if (k == count%10)
      return 1;
    count = count / 10;
  }
  return 0;
}


int main(void) {
  int n,k,i;
  scanf("%d %d", &n, &k);
  node_t Node[n];
  head = &Node[0];
  tail = &Node[n-1];
  for (i=0;i<n;i++) {
    Node[i].name = i+1;
    scanf("%d", &Node[i].alcohol);
  }
  //set next
  for (i=0;i<n-1;i++) {
    Node[i].next = &Node[i+1];
  }
  Node[n-1].next = &Node[0];
  //set prev
  for (i=1;i<n;i++) {
    Node[i].prev = &Node[i-1];
  }
  Node[0].prev = &Node[n-1];
  //printf("%d\n", Node[2].name);
  //show();
  //Delete(Node, Node[1]);
  int count = 1;
  node_t *current = head;
  while (1) {
    if (head->next->name == head->name)
      break;
    //printf("%d %d\n", current->name, current->alcohol);
    if (count % k == 0 || CheckDegit(count, k)) {
      current->alcohol -= 1;
    }
    if (current->alcohol == -1)
      Delete(Node, *current);
    current = current->next;
    count += 1;
  }
  printf("%d\n", head->name);
  //show();
  return 0;
}