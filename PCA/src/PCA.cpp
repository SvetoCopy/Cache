#include "PCA.h"
#include <algorithm>
#include "assert.h"
#include <iostream>

void dump(const std::unordered_map<int, std::queue<int>>& key_indexes,
          const std::unordered_map<int, Node>& elems, int put_elem) {
    
    for (const auto& pair : elems) {
        std::cout << pair.second.key << " ";
    }
    std::cout << "Curr elem: "<< put_elem << std::endl;

    std::cout << "Dump of key_indexes:" << std::endl;
    for (const auto& pair : key_indexes) {
        std::cout << "Key: " << pair.first << " -> ";
        const std::queue<int>& q = pair.second;
        std::queue<int> temp = q; 

        while (!temp.empty()) {
            std::cout << temp.front() << " ";
            temp.pop();
        }
        std::cout << std::endl;
    }
}

bool PCACache::getFreePlace(int key) {

    int next_index = key_indexes[key].front();

    int max_key = key;
    int max_index = next_index;

    for (const auto& elem_pair : elems) {
        int elem_key = elem_pair.second.key;
        const auto& indexes = key_indexes[elem_key];
        int elem_index = indexes.front();

        if (indexes.empty()) {
            elems.erase(elem_key);
            size--;
            return true;
        }

        else if (max_index < indexes.front()) {
            max_index = elem_index;
            max_key = elem_key;
        }
    }

    if (max_key != key) {
        elems.erase(max_key);
        size--;
        return true;
    }

    return false;
}

int PCACache::get(int key, int index) {

    auto find_node = elems.find(key);

    if (find_node == elems.end())
        return -1;

    auto curr_node = find_node->second;

    return curr_node.value;
}

bool PCACache::put(int key, int value, int index) {

    auto elem = elems.find(key);
    key_indexes[key].pop();

    if (elem == elems.end()) {
        if (key_indexes[key].empty()) return false;
        bool place_available = true;
        
        if (size >= capacity)
            place_available = getFreePlace(key);
            
        if (place_available) {
            elems[key] = Node(key, value);
            size++;
        }
    } else {
        if (key_indexes[key].empty()) {
            elems.erase(key);
            size--;
        }

        return true;
    }

    return false;
}

int PCACache::runHitCounting(std::istream& stream) {

    int num = 0;

    stream >> capacity >> num;

    std::vector<int> arr(num); 

    for (int i = 0; i < num; i++) {
        stream >> arr[i];
        key_indexes[arr[i]].push(i);
    }

    int hit_count = 0;
    
    for (int i = 0; i < num; i++) {
        hit_count += put(arr[i], i, i);
    }

    return hit_count;
}