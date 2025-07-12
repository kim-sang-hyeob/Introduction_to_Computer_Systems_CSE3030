#include <stdio.h>
#include <stdlib.h>
#include "multi_cache.h"



/*
reusing 하면 쉽게 구현 가능하다고 함.

*/
multi_cache_t* init_multi_cache_from_file(char *config_path) {
  /*
  config_path 입력 : 
  4 2 -> b / levl 
  1 2 -> E and s 
  4 4 -> E and s  
  첫번째 입력으로 b 랑 level 설정
  이후에는 levl 만큼 반복문 돌면서 single_cahche init 해주면될듯 ? 
  */


    FILE *config_fp;
    int b, n, E, s, ret;


    config_fp = fopen(config_path, "rt");
    ret = fscanf(config_fp, "%d %d", &b, &n); // 일단 첫줄 읽고 

    multi_cache_t *cache = (multi_cache_t*)malloc(sizeof(multi_cache_t));
    cache->n = n;
    cache->caches = (single_cache_t**)malloc(sizeof(single_cache_t*) * n);

    // 반복문 돌면서 각 줄마다 init_sigle cache 해준다. 
    for (int i = 0; i < n; i++) {
        fscanf(config_fp, "%d %d", &E, &s);
        cache->caches[i] = init_single_cache_with_param(b, E, s);
    }


    fclose(config_fp);
    return cache;
}

/*
 BA00
 BA04
 같은 입력을 받음 

 -> miss or hit at level 0 
*/
int access_with_multi_cache(multi_cache_t* cache, addr_t addr) {

  // 간단한 예외처리
  if (cache == NULL) return -1;
  if (cache->caches == NULL) return -1;
    
    // i 번쨰에 hit 한 경우 -> i 를 return . 
    for (int i = 0; i < cache->n; i++) {
        int tmp = access_with_single_cache(cache->caches[i], addr);
        if (tmp == 0) {
            return i;
        }
    }

    return -1;
}
