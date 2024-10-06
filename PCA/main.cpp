#include <iostream>
#include "PCA.h"
#include <fstream>
#include <vector>
#include <time.h>

int main(int argc, const char* argv[]) {

    if (argc < 1) {
		printf("Usage: %s input.txt\n", argv[0]);
		return -1;
	}

    int capacity = 0;
    int num = 0;

    std::ifstream input_file(argv[1]);

    if (!input_file.is_open()) {
        std::cerr << "Error in file openning!" << std::endl;
        return 1; 
    }

    input_file >> capacity >> num;

    std::vector<int> arr(num); 
    std::unordered_map<int, std::queue<int>> key_indexes;

    for (int i = 0; i < num; i++) {
        input_file >> arr[i];
        key_indexes[arr[i]].push(i);
    }

    PCACache lfu(capacity, key_indexes);

    std::cout << "Started Testing" << '\n';
    int hit_count = 0;

    clock_t start = clock();
    for (int i = 0; i < num; i++) {
        hit_count += lfu.put(arr[i], i, i);
    }

    clock_t end = clock();
    double seconds = (double)(end - start) / CLOCKS_PER_SEC;

    std::cout << "Time: " << seconds << "sec" << "\nHit count: " << hit_count << std::endl;
    input_file.close();
    
    return 0;
}