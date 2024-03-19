
#include <assert.h>
#include <stdio.h>
#include <time.h>

#include "LRU.h"

int main(void)
{
    srand(time(NULL));
    int size = 5;
    int times = 100;

    LRUCache *cache = lRUCacheCreate(size);
    
    for (int i = 0; i < times; i++) {
        int key = rand() % 10;
        int value = rand() % 100;

        if (rand() % 2) {
            printf("cache put:[%d, %d]\n", key, value);
            lRUCachePut(cache, key, value);
        } else {
            printf("cache get: %d, ", key);
            int value = lRUCacheGet(cache, key);
            printf("value = %d\n", value);
        }
    }

    lRUCacheFree(cache);


    return 0;
}