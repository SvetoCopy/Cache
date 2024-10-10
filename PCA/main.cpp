#include <iostream>
#include "PCA.h"
#include <fstream>
#include <vector>
#include <time.h>

int main() {

    int capacity = 0;
    int num = 0;

    std::cin >> capacity >> num;

    std::vector<int> arr(num); 
    std::unordered_map<int, std::queue<int>> key_indexes;

    for (int i = 0; i < num; i++) {
        std::cin >> arr[i];
        key_indexes[arr[i]].push(i);
    }

    PCACache lfu(capacity, key_indexes);

    #ifdef DEBUG
    std::cout << "Started Testing" << '\n';
    #endif

    int hit_count = 0;

    clock_t start = clock();
    for (int i = 0; i < num; i++) {
        hit_count += lfu.put(arr[i], i, i);
    }

    clock_t end = clock();

    #ifdef DEBUG
    double seconds = (double)(end - start) / CLOCKS_PER_SEC;
    std::cout << "Time: " << seconds << "sec" << "\n";
    #endif

    std::cout << hit_count << std::endl;

    return 0;
}