#include <unordered_map>
#include <list>
#include <queue>
#include <sstream>

namespace PCACache {
template<class KeyT, class ValueT>
struct Node {
    KeyT key;
    ValueT value;
};

template<class KeyT, class ValueT>
class PCACache {
private:
    std::unordered_map<KeyT, std::queue<int>> key_indexes;
    std::unordered_map<KeyT, Node<KeyT, ValueT>> elems;

    unsigned capacity;
    unsigned size;

    bool getFreePlace(const KeyT& key) {
        int next_index = key_indexes[key].front();

        KeyT max_key = key;
        int max_index = next_index;

        for (const auto& [elem_key, elem_node] : elems) {
            const auto& indexes = key_indexes[elem_key];
            int elem_index = indexes.front();

            if (indexes.empty()) {
                elems.erase(elem_key);
                size--;
                return true;
            }

            if (max_index < elem_index) {
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

public:
    PCACache(const unsigned capacity, const std::unordered_map<KeyT, std::queue<int>>& key_indexes):
            capacity{capacity}, key_indexes{key_indexes}, size{0} {};
    
    bool put(const KeyT& key, const ValueT& value, int index) {
        auto elem = elems.find(key);
        key_indexes[key].pop();

        if (elems.contains(key)) {
            if (key_indexes[key].empty()) {
                elems.erase(key);
                size--;
            }

            return true;
        }

        if (key_indexes[key].empty()) return false;
        bool place_available = true;
        
        if (size >= capacity)
            place_available = getFreePlace(key);
            
        if (place_available) {
            elems[key] = Node(key, value);
            size++;
        }

        return false;
    }
};
}