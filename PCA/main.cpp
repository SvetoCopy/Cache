#include <iostream>
#include "PCA.h"
#include <fstream>
#include <vector>
#include <time.h>

int main() {

    PCACache pca;
    std::cout << pca.runHitCounting(std::cin);

    return 0;
}