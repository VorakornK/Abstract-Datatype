#include<stdio.h>
#include<stdlib.h>

typedef struct cell {
    int data;
    int mem_addr;
} cell_t;

typedef struct hash {
    cell_t *table;
    int    cache_size;
} hash_t;

typedef hash_t cache_t;
typedef int    memory_t;

memory_t *init_memory(int size) {
    memory_t *memory = (memory_t *)malloc(sizeof(memory_t) * size); 
    int      i = 0;

    for (i=0; i<size; i++)
        memory[i] = rand();
    return memory;
}

cache_t *init_cache(int size) {
    cache_t *init = NULL;
    cell_t *ccell = NULL;
    init = (cache_t *)malloc(sizeof(cache_t));
    ccell = (cell_t *)malloc(sizeof(cell_t) * size);
    init->table = ccell;
    init->cache_size = size;
    return init;
} 

int cache_index(int addr, cache_t *cache) {
    return addr % cache->cache_size;
}

void get_data(int addr, memory_t *memory, cache_t *cache) {
    int cindex = cache_index(addr, cache);
    if (cache->table[cindex].data == 0) {
        cache->table[cindex].data = memory[addr];
        cache->table[cindex].mem_addr = addr;
        printf("Load from memory\n");
        printf("Data: %d\n", memory[addr]);
    }
    else if (cache->table[cindex].mem_addr != addr) {
        cache->table[cindex].data = memory[addr];
        cache->table[cindex].mem_addr = addr;
        printf("Index: %d is used\n", cindex);
        printf("Load from memory\n");
        printf("Data: %d\n", memory[addr]);
    }
    else if (cache->table[cindex].mem_addr == addr) {
        printf("Address %d is loaded\n", addr);
        printf("Data: %d\n", cache->table[cindex].data);
    }
}


int main(void) {
    memory_t *memory = NULL;
    cache_t *cache = NULL;
    int memory_size, cache_size;
    int i, n, addr;

    scanf("%d %d %d", &memory_size, &cache_size, &n);
    memory = init_memory(memory_size);
    cache = init_cache(cache_size);

    for (i=0; i<n; i++) {
        printf("Load address: ");
        scanf("%d", &addr);
        get_data(addr, memory, cache);
    }
}