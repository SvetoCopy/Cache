#include <gtest/gtest.h>
#include "PCA.h"
#include "LFU.h"
#include <fstream>
#include <sstream>

int testLFUFromStream(std::istream& stream) {
    int num = 0;
    unsigned capacity = 0;

    stream >> capacity >> num;
    int key;
    int hit_count = 0;

    LFUCache::LFUCache<int, int> lfu(capacity);
    
    for (int i = 0; i < num; i++) {
        stream >> key;
        hit_count += lfu.put(key, i);
    }

    return hit_count;
}

static int testPCAFromStream(std::istream& stream) {
    int num = 0;
    int capacity = 0;

    stream >> capacity >> num;

    std::vector<int> arr(num); 
    std::unordered_map<int, std::queue<int>> key_indexes;

    for (int i = 0; i < num; i++) {
        stream >> arr[i];
        key_indexes[arr[i]].push(i);
    }

    PCACache::PCACache<int, int> pca(capacity, key_indexes);

    int hit_count = 0;
    
    for (int i = 0; i < num; i++) {
        hit_count += pca.put(arr[i], i, i);
    }

    return hit_count;
}

TEST(PCATests, test1) {

    std::ifstream file("../002.txt"); 

    std::stringstream buffer;
    buffer << file.rdbuf();

    int hit_count = testPCAFromStream(buffer);
    ASSERT_TRUE(hit_count == 65);
    
    file.close();
}

TEST(PCATests, test2) {
    std::ifstream file("../001.dat"); 

    std::stringstream buffer;
    buffer << file.rdbuf();
    int hit_count = testPCAFromStream(buffer);

    ASSERT_TRUE(hit_count == 7);

    file.close();
}

TEST(PCATests, test3) {

    std::ifstream file("../015.dat"); 

    std::stringstream buffer;
    buffer << file.rdbuf();

    int hit_count = testPCAFromStream(buffer);
    
    ASSERT_TRUE(hit_count == 124450);
    
    file.close();
}

TEST(PCATests, test4) {
  
    std::ifstream file("../011.dat"); 

    std::stringstream buffer;
    buffer << file.rdbuf();

    int hit_count = testPCAFromStream(buffer);
    
    ASSERT_TRUE(hit_count == 89999);
    
    file.close();
}

TEST(LFUTests, test1) {
    std::ifstream file("../011.dat"); 

    std::stringstream buffer;
    buffer << file.rdbuf();
    int hit_count = testLFUFromStream(buffer);
    
    ASSERT_TRUE(hit_count == 89999);
    
    file.close();
}

TEST(LFUTests, test3) {
    std::ifstream file("../012.dat"); 

    std::stringstream buffer;
    buffer << file.rdbuf();
    int hit_count = testLFUFromStream(buffer);

    ASSERT_TRUE(hit_count == 113501);

    file.close();
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}