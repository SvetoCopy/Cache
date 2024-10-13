#include <unordered_map>
#include <list>
#include <queue>
#include <sstream>

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

    int get(int key, int index);
    bool put(int key, int value, int index);
    bool getFreePlace(int key);

public:
    int runHitCounting(std::istream& stream);
};