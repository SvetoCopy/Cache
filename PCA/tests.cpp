#include <gtest/gtest.h>
#include "PCA.h"
#include <fstream>
#include <sstream>

using namespace std;

TEST(PCATests, test1) {

    PCACache pca;
    std::ifstream file("../tests/002.txt"); 

    std::stringstream buffer;
    buffer << file.rdbuf();

    int hit_count = pca.runHitCounting(buffer);

    std::cout << hit_count;
    
    ASSERT_TRUE(hit_count == 65);
    
    file.close();
}

TEST(PCATests, test2) {
  
    PCACache pca;
    std::ifstream file("../tests/001.dat"); 

    std::stringstream buffer;
    buffer << file.rdbuf();
    int hit_count = pca.runHitCounting(buffer);

    ASSERT_TRUE(hit_count == 7);

    file.close();
}

TEST(PCATests, test3) {
  
    PCACache pca;
    std::ifstream file("../tests/015.dat"); 

    std::stringstream buffer;
    buffer << file.rdbuf();
    int hit_count = pca.runHitCounting(buffer);

    ASSERT_TRUE(hit_count == 124450);

    file.close();
}

TEST(PCATests, test4) {
  
    PCACache pca;
    std::ifstream file("../tests/011.dat"); 

    std::stringstream buffer;
    buffer << file.rdbuf();
    int hit_count = pca.runHitCounting(buffer);

    ASSERT_TRUE(hit_count == 89999);

    file.close();
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}