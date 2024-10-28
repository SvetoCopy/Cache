#include <iostream>
#include "PCA.h"
#include <fstream>
#include <vector>
#include <time.h>

int main() {
    int num = 0;
    int capacity = 0;

    std::cin >> capacity >> num;

    std::vector<int> arr(num); 
    std::unordered_map<int, std::queue<int>> key_indexes;

    for (int i = 0; i < num; i++) {
        std::cin >> arr[i];
        key_indexes[arr[i]].push(i);
    }

    PCACache::PCACache<int, int> pca(capacity, key_indexes);

    int hit_count = 0;
    
    for (int i = 0; i < num; i++) {
        hit_count += pca.put(arr[i], i, i);
    }

    std::cout << hit_count;

    return 0;
}