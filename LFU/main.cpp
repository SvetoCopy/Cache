#include <iostream>
#include "LFU.h"
#include <fstream>
#include <vector>
#include <time.h>

int runHitCounting(std::istream& stream) {
    int num = 0;
    unsigned capacity = 0;

    stream >> capacity >> num;
    int key;
    int hit_count = 0;

    LFUCache::LFUCache<int, int> lfu(capacity);
    

    for (int i = 0; i < num; i++) {
        stream >> key;
        hit_count += lfu.put(key, i);
    }

    return hit_count;
}

int main() {
    std::cout << runHitCounting(std::cin);

    return 0;
}