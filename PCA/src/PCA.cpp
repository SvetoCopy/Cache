#include "PCA.h"
#include <algorithm>
#include "assert.h"
#include <iostream>

bool PCACache::getFreePlace(int key, int index) {

    if (key_indexes[key].empty()) return false;

    int next_index = key_indexes[key].front();
    assert(next_index > index);

    if (next_index < key_indexes[most_far.key].front()) {
        elems.erase(most_far.key);
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

void PCACache::updateMinMax() {

    int begin_elem_key = elems.begin()->second.key;

    most_far = elems.begin()->second;
    int max_index = key_indexes[begin_elem_key].front();

    for (auto elem : elems) {
        if (key_indexes[elem.second.key].empty()) {
            most_far = elem.second;
            break;
        }
        
        int elem_index = key_indexes[elem.second.key].front();

        if (elem_index > max_index) {
            max_index = elem_index;
            most_far = elem.second;
        }
    }
}

bool PCACache::put(int key, int value, int index) {

    auto elem = elems.find(key);
    key_indexes[key].pop();

    if (elem == elems.end()) {
        bool place_available = true;
        
        if (size >= capacity) 
            place_available = getFreePlace(key, index);
        
        if (place_available) {
            elems[key] = Node(key, value);
            size++;
            updateMinMax();
        }
    } else if (get(key, index) != -1) {
        updateMinMax();
        return true;
    }

    return false;
}