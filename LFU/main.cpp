#include <iostream>
#include "LFU.h"
#include <fstream>
#include <vector>
#include <time.h>

int main() {

    LFUCache<int, int> lfu;

    std::cout << (lfu.runHitCounting(std::cin));

    
    return 0;
}