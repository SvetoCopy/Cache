#include <unordered_map>
#include <list>
#include <queue>
#include <sstream>

#define INT_MAX_VALUE 2147483647

template<class KeyT, class ValueT>
struct Node {
    KeyT key;
    ValueT value;
    Node(KeyT key, ValueT val): key{key}, value{val} {};
    Node() {};
};

template<class KeyT, class ValueT>
class PCACache {
private:
    std::unordered_map<KeyT, std::queue<int>> key_indexes;
    std::unordered_map<KeyT, Node<KeyT, ValueT>> elems;

    unsigned capacity;
    unsigned size;

    bool getFreePlace(KeyT key) {
        int next_index = key_indexes[key].front();

        KeyT max_key = key;
        int max_index = next_index;

        for (const auto& elem_pair : elems) {
            KeyT elem_key = elem_pair.second.key;
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

    ValueT get(KeyT key) {
        auto find_node = elems.find(key);

        if (find_node == elems.end())
            return -1;

        auto curr_node = find_node->second;

        return curr_node.value;
    }

    bool put(KeyT key, ValueT value, int index) {
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

public:
    int runHitCounting(std::istream& stream) {
        int num = 0;

        stream >> capacity >> num;

        std::vector<KeyT> arr(num); 

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
};