#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct node {
    char *word;
    int freq;
    struct node *left;
    struct node *right;
} tree_t;

typedef struct heap {
    tree_t **node;
    int last_index;
} heap_t;

heap_t *init(int n) {
    tree_t **anode = (tree_t**)malloc(sizeof(tree_t*) * (n+1));
    heap_t *new = (heap_t *)malloc(sizeof(heap_t));
    new->node = anode;
    new->last_index = 1;
    return new;
}

void print(heap_t *min_heap) {
    for (int i=1; i<min_heap->last_index; i++) {
        tree_t *this = min_heap->node[i];
        printf("%s %d  ", this->word, this->freq);
    }
    printf("\n");
}

void swap(heap_t *min_heap, int i) {
    tree_t *tmp = min_heap->node[i];
    min_heap->node[i] = min_heap->node[i/2];
    min_heap->node[i/2] = tmp;
}

void balance(heap_t *min_heap, int i) {
    if (i > 1) {
        tree_t *parent = min_heap->node[i/2];
        tree_t *child = min_heap->node[i];
        while (i > 1 && child->freq < parent->freq) {
            swap(min_heap, i);
            i/=2;  
            parent = min_heap->node[i/2];
            child = min_heap->node[i];
        }
    }
}


void basicin(heap_t *min_heap, char *word, int fre) {
    int lastempty = min_heap->last_index;
    tree_t *add;
    add = (tree_t*)malloc(sizeof(tree_t));
    add->word = word;
    add->freq = fre;
    min_heap->node[lastempty] = add;
    balance(min_heap, lastempty);
    min_heap->last_index++;
}

void insertNode(heap_t *min_heap, tree_t *node) {
    int lastempty = min_heap->last_index;
    min_heap->node[lastempty] = node;
    balance(min_heap, lastempty);
    min_heap->last_index++;
}

void delete_min(heap_t *min_heap) {
    if (min_heap->last_index != 1) {
        tree_t *at1 = min_heap->node[1];
        tree_t *atlast = min_heap->node[min_heap->last_index-1];
        min_heap->node[1] = atlast;
        min_heap->last_index--;
        int x = 1;
        while (2*x < min_heap->last_index) {
            at1 = min_heap->node[x];
            tree_t *child1 = min_heap->node[2*x];
            if ((2*x)+1 < min_heap->last_index) {
                tree_t *child2 = min_heap->node[2*x+1];
                if (child1->freq >= at1->freq && child2->freq >= at1->freq) break;
                if (child1->freq <= child2->freq) {
                    swap(min_heap, 2*x);
                    x = 2*x;
                }
                else if (child1->freq > child2->freq) {
                    swap(min_heap, 2*x+1);
                    x = (2*x)+1;
                }
            }
            else {
                if (child1->freq >= at1->freq) break;
                swap(min_heap, 2*x);
                x = 2*x;
            }

        }
    }
}

void tree_get(heap_t *min_heap) {
    tree_t *first = NULL;
    tree_t *second = NULL;
    while (min_heap->last_index != 2) {
        tree_t *new = (tree_t *)malloc(sizeof(tree_t));
        first = min_heap->node[1];
        delete_min(min_heap);
        second = min_heap->node[1];
        delete_min(min_heap);
        new->word = "A";
        new->left = first;
        new->right = second;
        new->freq = first->freq + second->freq;
        insertNode(min_heap, new);
    }
}



void print_tree_2(tree_t *t, int depth, char pre){
  int i;
  if (t == NULL)
    return;
  for (i=0; i<depth; i++)
    printf("    ");
  printf("%c%s\n", pre, t->word);
  print_tree_2(t->left, depth+1, 'L');
  print_tree_2(t->right, depth+1, 'R');
}

void print_tree(tree_t *t){
  print_tree_2(t, 0, 'r');
}

void dfs(tree_t *t, char *w) {
    if (t!=NULL) {
    char *placeholder = "A";
    if(t->word != placeholder) printf("%s: %s\n", t->word, w);
    char w1[100], w2[100];
    strcpy(w1, w);
    strcpy(w2, w);
    strcat(w1, "0");
    strcat(w2, "1");
    dfs(t->left, w1); 
    dfs(t->right, w2);
    } 
}


int main() {
    heap_t *min_heap = NULL;
    int n=6, i, freq;
    scanf("%d", &n);
    min_heap = init(n);
    for (i=0; i<n; i++) {
        char *word = (char*)malloc(sizeof(char) * 15);
        scanf("%s %d", word, &freq);
        basicin(min_heap, word, freq);
    }
    tree_get(min_heap);
    dfs(min_heap->node[1], "");
    return 0;
}