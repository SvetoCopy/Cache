#include <unordered_map>
#include <list>
#include <sstream>

namespace LFUCache {
template<class KeyT, class ValueT>
struct Node {
    KeyT key;
    ValueT value;
    unsigned freq;
};

template<class KeyT, class ValueT>
class LFUCache {
private:
    std::unordered_map<unsigned, std::list<Node<KeyT, ValueT>>> freq;

    using freq_list_it = typename std::list<Node<KeyT, ValueT>>::iterator;

    std::unordered_map<KeyT, freq_list_it> elems;

    unsigned min_freq;
    unsigned capacity;
    unsigned size;
    
    void updateNodeFreq(freq_list_it curr_node) {
        Node<KeyT, ValueT> node = *curr_node;

        std::list<Node<KeyT, ValueT>>& curr_freq_list = freq[node.freq];
        curr_freq_list.erase(curr_node);

        if (curr_freq_list.empty() && min_freq == node.freq)
            min_freq++;

        freq[node.freq].push_front(Node<KeyT, ValueT>(node.key, node.value, node.freq));
        elems[(*curr_node).key] = freq[node.freq].begin();
    }

    void getFreePlace() {
        std::list<Node<KeyT, ValueT>>& min_freq_list = freq[min_freq];
        freq_list_it node_to_delete = std::prev(min_freq_list.end());

        elems.erase((*node_to_delete).key);
        min_freq_list.erase(node_to_delete);

        min_freq = 0;
    }

public:
    LFUCache(const unsigned capacity): capacity{capacity}, size{0} {};

    bool put(const KeyT& key, const ValueT& value) {
        auto elem = elems.find(key);

        if (elem != elems.end()) {
            updateNodeFreq(elem->second);
            return true;
        }
        else {
            if (size >= capacity)
                getFreePlace();
            
            freq[0].push_front(Node<KeyT, ValueT>(key, value, 0));
            freq_list_it it = freq[0].begin();

            elems[key] = it;
            min_freq = 0;
            size++;

            return false;
        }
    }
};
}
