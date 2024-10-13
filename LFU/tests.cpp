#include <gtest/gtest.h>
#include "LFU.h"
#include <fstream>
#include <sstream>

using namespace std;

TEST(TestGroupName, Subtest_1) {

    LFUCache lfu;
    std::ifstream file("../tests/011.dat"); 

    std::stringstream buffer;
    buffer << file.rdbuf();
    int hit_count = lfu.runHitCounting(buffer);
    
    ASSERT_TRUE(hit_count == 89999);
    
    file.close();
}

TEST(TestGroupName, Subtest_3) {
  
    LFUCache lfu;
    std::ifstream file("../tests/012.dat"); 

    std::stringstream buffer;
    buffer << file.rdbuf();
    int hit_count = lfu.runHitCounting(buffer);

    ASSERT_TRUE(hit_count == 113501);

    file.close();
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}