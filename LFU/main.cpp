#include <iostream>
#include "LFU.h"
#include <fstream>
#include <vector>
#include <time.h>

int main() {
    int num = 0;
    unsigned capacity = 0;

    std::cin >> capacity >> num;
    int key;
    int hit_count = 0;

    LFUCache::LFUCache<int, int> lfu(capacity);
    
    for (int i = 0; i < num; i++) {
        std::cin >> key;
        hit_count += lfu.put(key, i);
    }

    std::cout << hit_count;

    return 0;
}