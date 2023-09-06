#include <sdsl/vectors.hpp>
#include <iostream>

// g++ -std=c++11 -g -O3 -DNDEBUG -I ~/include -L ~/lib write_ints.cpp -o write_ints -lsdsl

using namespace std;
using namespace sdsl;

#define N 8

int main() {
    string file = "integers.sdsl";
    auto vec = int_vector<>({1, 2, 3, 7, 1, 4});
    store_to_file(vec, file.c_str());
    return 0;
}