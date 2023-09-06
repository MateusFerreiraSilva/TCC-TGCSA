#include <sdsl/vectors.hpp>
#include <iostream>

// g++ -std=c++11 -g -O3 -DNDEBUG -I ~/include -L ~/lib read_ints.cpp -o read_ints -lsdsl

using namespace std;
using namespace sdsl;

#define N 8

int main() {
    string file = "integers.sdsl";
    int_vector<> vec;
    load_from_file(vec, file.c_str());
    cout << vec << endl;
    return 0;
}