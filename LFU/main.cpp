#include <iostream>
#include "LFU.h"
#include <fstream>
#include <vector>
#include <time.h>

int main() {

    LFUCache lfu;
    std::ifstream file("/home/rusal/Desktop/Vladimirov/Cache/tests/012.dat"); 

    std::stringstream buffer;
    buffer << file.rdbuf();

    std::cout << (lfu.runHitCounting(buffer) == 113501);

    file.close();
    
    return 0;
}