#include <unordered_map>
#include <list>

struct Node {
    int key;
    int value;
    int freq;
    Node(int key, int val, int freq): key{key}, value{val}, freq{freq} {};
};

class LFUCache {
private:
    std::unordered_map<int, std::list<Node>> freq;
    std::unordered_map<int, std::list<Node>::iterator> elems;

    int min_freq;
    unsigned capacity;
    unsigned size;
    
    void updateNodeFreq(std::list<Node>::iterator curr_node); 

public:
    LFUCache(unsigned capacity):capacity{capacity}, size{0} {};

    int get(int key);
    bool put(int key, int value);
    void getFreePlace();
};