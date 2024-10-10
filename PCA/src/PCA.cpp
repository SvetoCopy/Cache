#include "PCA.h"
#include <algorithm>
#include "assert.h"
#include <iostream>

void dump(const std::unordered_map<int, std::queue<int>>& key_indexes,
          const std::unordered_map<int, Node>& elems) {
    
    for (const auto& pair : elems) {
        std::cout << pair.second.key << " ";
    }
    std::cout << std::endl;

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

    if (key_indexes[key].empty()) return false;

    int next_index = key_indexes[key].front();

    for (const auto& elem_pair : elems) {
        int elem_key = elem_pair.second.key;
        const auto& indexes = key_indexes[elem_key];

        if (indexes.empty() || next_index < indexes.front()) {
            elems.erase(elem_key);
            size--;
            return true;
        }
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
        bool place_available = true;
        
        if (size >= capacity)
            place_available = getFreePlace(key);
            
        if (place_available) {
            elems[key] = Node(key, value);
            size++;
        }
    } else if (get(key, index) != -1)
        return true;

    return false;
}