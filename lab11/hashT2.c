#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define TEXTSIZE 21

typedef char* item_t;

typedef struct hash {
    item_t *table;
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
    item_t *tble = NULL;
    init = (hash_t *)malloc(sizeof(hash_t));
    tble = (item_t *)malloc(sizeof(item_t) * m);
    init->table = tble;
    init->size = m;
    init->hash_key = hash_key;
    return init;
}

void insert(hash_t *hashtable, char *text) {
    int hhash = hash(text, hashtable->hash_key, hashtable->size) ;
    char *ttext = NULL;
    ttext = (char *)malloc(sizeof(char) * TEXTSIZE);
    strcpy(ttext, text);
    if (hashtable->table[hhash] == NULL) hashtable->table[hhash] = ttext;
    else {
        int i = 0;
        int hhhash = hhash;
        while (hashtable->table[hhhash] != NULL) {
            hhhash = hhash + (i + i*i)/2;
            hhhash = hhhash % hashtable->size;
            i++;
        }
        hashtable->table[hhhash] = ttext;
    }
}

int search(hash_t *hashtable, char *text) {
    int hhash = hash(text, hashtable->hash_key, hashtable->size);
    int hhhash = hhash;
    int i = 0;
    while (hashtable->table[hhhash] != NULL) {
        if (strcmp(hashtable->table[hhhash], text) == 0) return hhhash;
        hhhash = hhash + (i + i*i)/2;
        hhhash = hhhash % hashtable->size;
        i++;
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

/*
13 10 19
1 qwert
1 asdf
1 zklwo
1 a

2 qwert
2 qwerty
2 a
2 asdf
2 omg
2 abcd

211 20 93
1 abcd
1 abdc
1 afnc
1 oog
1 ozg
1 obg
1 obp
1 fjdlo
1 auvun
1 adzlr
2 abcd
2 abdc
2 afnc
2 oog
2 ozg
2 obg
2 obp
2 fjdlo
2 auvun
2 adzlr

31 14 19
1 mhewrv
1 rkrfni
1 wtabik
1 ibpffi
1 hwrthu
1 mcpsnn
1 xmyprx
2 mhewrv
2 rkrfni
2 wtabik
2 ibpffi
2 hwrthu
2 mcpsnn
2 xmyprx

*/