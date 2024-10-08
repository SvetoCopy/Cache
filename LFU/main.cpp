#include <iostream>
#include "LFU.h"
#include <fstream>
#include <vector>
#include <time.h>

int main() {

    int capacity = 0;
    int num = 0;

    std::cin >> capacity >> num;

    LFUCache lfu(capacity);
    std::vector<int> arr(num); 

    for (int i = 0; i < num; i++) {
        std::cin >> arr[i];
    }

    std::cout << "Started Testing" << '\n';
    int hit_count = 0;

    clock_t start = clock();
    for (int i = 0; i < num; i++) {
        hit_count += lfu.put(arr[i], i);
    }

    clock_t end = clock();
    double seconds = (double)(end - start) / CLOCKS_PER_SEC;

    std::cout << "Time: " << seconds << "sec" << "\nHit count: " << hit_count << std::endl;
    
    return 0;
}