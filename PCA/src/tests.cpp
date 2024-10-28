#include <gtest/gtest.h>
#include "PCA.h"
#include <fstream>
#include <sstream>

using namespace std;

static int testFileBuffer(std::istream& stream) {
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

    std::ifstream file("../tests/002.txt"); 

    std::stringstream buffer;
    buffer << file.rdbuf();

    int hit_count = testFileBuffer(buffer);
    ASSERT_TRUE(hit_count == 65);
    
    file.close();
}

TEST(PCATests, test2) {
    std::ifstream file("../tests/001.dat"); 

    std::stringstream buffer;
    buffer << file.rdbuf();
    int hit_count = testFileBuffer(buffer);

    ASSERT_TRUE(hit_count == 7);

    file.close();
}

TEST(PCATests, test3) {

    std::ifstream file("../tests/015.dat"); 

    std::stringstream buffer;
    buffer << file.rdbuf();

    int hit_count = testFileBuffer(buffer);
    
    ASSERT_TRUE(hit_count == 124450);
    
    file.close();
}

TEST(PCATests, test4) {
  
    std::ifstream file("../tests/011.dat"); 

    std::stringstream buffer;
    buffer << file.rdbuf();

    int hit_count = testFileBuffer(buffer);
    
    ASSERT_TRUE(hit_count == 89999);
    
    file.close();
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}