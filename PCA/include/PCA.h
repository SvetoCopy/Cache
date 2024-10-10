#include <unordered_map>
#include <list>
#include <queue>

#define INT_MAX_VALUE 2147483647

struct Node {
    int key;
    int value;
    Node(int key, int val): key{key}, value{val} {};
    Node() {};
};

class PCACache {
private:
    std::unordered_map<int, std::queue<int>> key_indexes;
    std::unordered_map<int, Node> elems;

    unsigned capacity;
    unsigned size;

public:
    PCACache(unsigned capacity, std::unordered_map<int, std::queue<int>> key_indexes): 
            capacity{capacity}, size{0}, key_indexes{key_indexes} {};

    int get(int key, int index);
    bool put(int key, int value, int index);
    bool getFreePlace(int key);
};