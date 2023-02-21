#include<stdio.h>
#include<stdlib.h>

typedef struct cell{
    int data;
    int mem_addr;
} cell_t;

typedef struct hash{
    cell_t *table;
    int cache_size;
} hash_t;

typedef hash_t cache_t;
typedef int memory_t;

memory_t *init_memory(int size){
    memory_t *memory = (memory_t *)malloc(sizeof(memory_t)*size);
    int i=0;

    //Randomly assign integers to memory
    for(i=0;i<size;i++)
        memory[i]=rand();
    return memory;
}

cell_t *init_cachedata(int size){
    cell_t *it=(cell_t *)malloc(sizeof(cell_t )*size);
    for(int i=0;i<size;i++){
        it[i].data=-1;
    }
    return it;
}
cache_t *init_cache(int size){
    cache_t *c=(cache_t *)malloc(sizeof(cache_t));
    c->table=init_cachedata(size);
    c->cache_size=size;
    return c;
}

int cache_index(int addr,cache_t *c){
    return addr%c->cache_size;
}

void get_data(int addr,memory_t *mem,cache_t *c){
    int pos=cache_index(addr, c);
    if(c->table[pos].data==-1){
        c->table[pos].data=mem[addr];
        c->table[pos].mem_addr=addr;
        printf("Load from memory\n");
    } else if(addr!=c->table[pos].mem_addr){
        printf("Index %d is used\n",pos);
        printf("Load from memory\n");
        c->table[pos].data=mem[addr];
        c->table[pos].mem_addr=addr;
    } else if(c->table[pos].mem_addr==addr){
        printf("Address %d is loaded\n",addr);
    }
    printf("Data: %d\n",c->table[pos].data);
}
int main(void){
    memory_t *memory=NULL;
    cache_t *cache=NULL;
    int memory_size, cache_size;
    int i,n,addr;

    scanf("%d %d %d", &memory_size, &cache_size, &n);
    memory=init_memory(memory_size);
    cache=init_cache(cache_size);

    for(i=0;i<n;i++){
        printf("Load address: ");
        scanf("%d", &addr);
        get_data(addr, memory, cache);
    }
    return 0;
}
/*
100 10 10
10
20
20
15
73
50
14
94
78
94

50 15 10
4
4
13
6
4
12
17
5
11
6

20 4 10
18
19
9
16
0
12
0
9
11
10
*/