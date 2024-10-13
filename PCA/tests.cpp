#include <gtest/gtest.h>
#include "PCA.h"
#include <fstream>
#include <sstream>

using namespace std;

TEST(TestGroupName, Subtest_1) {

    PCACache pca;
    std::ifstream file("../tests/input.txt"); 

    std::stringstream buffer;
    buffer << file.rdbuf();

    int hit_count = pca.runHitCounting(buffer);

    std::cout << hit_count;
    
    ASSERT_TRUE(hit_count == 65);
    
    file.close();
}

TEST(TestGroupName, Subtest_3) {
  
    PCACache pca;
    std::ifstream file("../tests/012.dat"); 

    std::stringstream buffer;
    buffer << file.rdbuf();
    int hit_count = pca.runHitCounting(buffer);

    ASSERT_TRUE(hit_count == 113501);

    file.close();
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}