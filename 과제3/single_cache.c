#include <stdio.h>
#include <stdlib.h>
#include "types.h"
#include "single_cache.h"

typedef struct cache_line_t * cache_set_t;


single_cache_t* init_single_cache_from_file(char *config_path) {
  int b, E, s, ret;
  FILE *config_fp;

  config_fp = fopen(config_path, "rt");
  if (config_fp == NULL) {
    printf("Failed to open configuration file %s\n", config_path);
    return NULL;
  }

  ret = fscanf(config_fp, "%d %d %d", &b, &E, &s);
  if (ret != 3) {
    printf("Invalid configuration format\n");
    return NULL;
  }
  fclose(config_fp);

  if (b <= 0 || E <= 0 || s <= 0 || b > 16 || s > 16) {
    printf("Invalid configuration parameter: b=%d, E=%d, s=%d\n", b, E, s);
    return NULL;
  }

  return init_single_cache_with_param(b, E, s);
}

/*
구조체 확인용
typedef struct cache_line_t {
  int valid_flag;
  addr_t tag;
  int age;
} cache_line_t;

// Type for single-level cache memory.
typedef struct _single_cache_t {
  int b; // Number of block offset bits.
  int B; // Size of cache block.
  int E; // Number of cache lines per set.
  int s; // Number of set index bits.
  int S; // Number of sets in the cache memory.
  cache_set_t* sets; // Pointer to an array of cache sets.
} single_cache_t;
*/

static int lru_helper = 0;

single_cache_t* init_single_cache_with_param(int b, int E, int s) {
  single_cache_t *cache = malloc(sizeof(single_cache_t));
  // TODO: Implement this function.

  cache->b = b; 
  cache->E = E;
  cache->s = s;
  cache->S = 1<<s;
  cache->B = 1<<b;

  // Allocate the array of cache sets.
  cache->sets = (cache_set_t*)malloc(sizeof(cache_set_t) * cache->S);

   for (int i = 0; i < cache->S; i++) {
        cache->sets[i] = (cache_line_t*)malloc(sizeof(cache_line_t) * cache->E);

        // 초기화해주어야함 
        for (int j = 0; j < cache->E; j++) {
            cache->sets[i][j].tag = 0;
            cache->sets[i][j].valid_flag = 0;
            cache->sets[i][j].age = 0;
        }
    }

    lru_helper = 0;
    return cache;
}


int access_with_single_cache(single_cache_t* cache, addr_t addr) {
  // TODO: Implement this function.
    lru_helper++;

    int set = (addr >> cache->b) & ((1 << cache->s) - 1); // set 부분 계산하도록 
    addr_t tag = addr >> (cache->s + cache->b); 

    cache_set_t curent_set = cache->sets[set]; // 현재 검사할 set 가지고오기 

    // cache hit 검사하기 
    for (int i = 0; i < cache->E; i++) {
        // 만약에 hit 라면 
        if (curent_set[i].valid_flag && curent_set[i].tag == tag) {
            curent_set[i].age = lru_helper;
            return 0;
        }
    }

    // 만약 miss 였다면 -> 갱신 
    for (int i = 0; i < cache->E; i++) {
        if (!curent_set[i].valid_flag) {
            curent_set[i].tag = tag;
            curent_set[i].valid_flag = 1;
            curent_set[i].age = lru_helper;
            return -1; // miss 인경우 -1 return 하기 
        }
    }

    // Lru 
    int lru_index = 0;
    int flag = curent_set[0].age;
    for (int i = 1; i < cache->E; i++) {
        if (curent_set[i].age < flag) {
            flag = curent_set[i].age;
            lru_index = i;
        }
    }

    curent_set[lru_index].tag = tag;
    curent_set[lru_index].age = lru_helper;

    return -1; 
}
