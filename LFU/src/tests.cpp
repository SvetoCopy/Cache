#include <gtest/gtest.h>
#include "LFU.h"
#include <fstream>
#include <sstream>

int runHitCounting(std::istream& stream) {
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

TEST(TestGroupName, Subtest_1) {
    std::ifstream file("../tests/011.dat"); 

    std::stringstream buffer;
    buffer << file.rdbuf();
    int hit_count = runHitCounting(buffer);
    
    ASSERT_TRUE(hit_count == 89999);
    
    file.close();
}

TEST(TestGroupName, Subtest_3) {
    std::ifstream file("../tests/012.dat"); 

    std::stringstream buffer;
    buffer << file.rdbuf();
    int hit_count = runHitCounting(buffer);

    ASSERT_TRUE(hit_count == 113501);

    file.close();
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}