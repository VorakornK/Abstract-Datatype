#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define TEXTSIZE 21

typedef struct item {
    char *text;
    struct item *next;
} item_t;

typedef struct hash {
    item_t **table;
    int size;
    int hash_key;
} hash_t;

char *atd(char *text) {
    int size = strlen(text);
    char *a = (char *)malloc(sizeof(char) * TEXTSIZE);
    strcpy(a, text);
    a[size-1] = '\0';
    return a;
}

int last(char *text) {
    return text[strlen(text)-1];
}
 
unsigned int f(int n, int hash_key, char *text) {
    if (n == 0) return text[0];
    char x[21];
    strcpy(x, text);
    return hash_key * f(n-1, hash_key, atd(x)) + last(text);
}

int hash(char *text, int hash_key, int size) {
    return f(strlen(text), hash_key, text)%size;
}

hash_t *init_hashtable(int m, int hash_key) {
    hash_t *init = NULL;
    item_t **tble = NULL;
    tble = (item_t **)malloc(sizeof(item_t) * m);
    init = (hash_t *)malloc(sizeof(hash_t));
    init->table = tble;
    init->size = m;
    init->hash_key = hash_key;
    return init;
}

void insert(hash_t *hashtable, char *text) {
    int hhash = hash(text, hashtable->hash_key, hashtable->size);
    //char ttext[TEXTSIZE];
    char *ttext = NULL;
    ttext = (char *)malloc(sizeof(char) * TEXTSIZE);
    strcpy(ttext, text);
    item_t **tble = hashtable->table;
    item_t *new = NULL;
    new = (item_t *)malloc(sizeof(item_t));
    new->text = ttext;
    if (tble[hhash] == NULL) tble[hhash] = new;
    else {
        item_t *current = tble[hhash];
        while (current->next != NULL) {
            current = current->next;
            }
        current->next = new;
    }
}

int search(hash_t *hashtable, char *text) {
    int hhash = hash(text, hashtable->hash_key, hashtable->size);
    item_t **tble = hashtable->table;
    item_t *current = tble[hhash];
    if (current != NULL && strcmp(current->text, text) == 0) return hhash;
    while (current != NULL) {
        if (strcmp(current->text, text) == 0) return hhash;
        current = current->next;
    }
    return -1;
}


int main(void) {
    hash_t *hashtable = NULL;
    char *text = NULL;
    int m, n, i, hash_key;
    int command;

    scanf("%d %d %d", &m, &n, &hash_key);
    hashtable = init_hashtable(m, hash_key);
    text = (char *)malloc(sizeof(char) * TEXTSIZE);
    
    for (i=0; i<n; i++) {
        scanf("%d %s", &command, text);
        switch (command) {
            case 1:
                insert(hashtable, text);
                break;
            case 2:
                printf("%d\n", search(hashtable, text));
                break;
        }
    }
    return 0;
}
