#include "LFU.h"
#include <algorithm>
#include "assert.h"

void LFUCache::updateNodeFreq(std::list<Node>::iterator curr_node) {

    Node node = *curr_node;

    std::list<Node>& curr_freq_list = freq[node.freq];
    curr_freq_list.erase(curr_node);

    if (curr_freq_list.empty() && min_freq == node.freq)
        min_freq++;

    freq[node.freq].push_front(Node(node.key, node.value, node.freq));
    elems[(*curr_node).key] = freq[node.freq].begin();
}

void LFUCache::getFreePlace() {

    std::list<Node>& min_freq_list = freq[min_freq];
    std::list<Node>::iterator node_to_delete = std::prev(min_freq_list.end());

    elems.erase((*node_to_delete).key);
    min_freq_list.erase(node_to_delete);

    min_freq = 0;
}

int LFUCache::get(int key) {

    auto find_node = elems.find(key);

    if (find_node == elems.end())
        return -1;

    auto curr_node = find_node->second;
    updateNodeFreq(curr_node);

    return (*curr_node).value;
}

bool LFUCache::put(int key, int value) {

    auto elem = elems.find(key);

    if (elem == elems.end()) {
        if (size >= capacity)
            getFreePlace();
        
        freq[0].push_front(Node(key, value, 0));
        std::list<Node>::iterator it = freq[0].begin();

        elems[key] = it;
        min_freq = 0;
        size++;
    } else if (get(key) != -1) return true;

    return false;
}

int LFUCache::runHitCounting(std::istream& stream) {

    int num = 0;

    stream >> capacity >> num;
    int key;
    int hit_count = 0;

    for (int i = 0; i < num; i++) {
        stream >> key;
        hit_count += put(key, i);
    }

    return hit_count;
}