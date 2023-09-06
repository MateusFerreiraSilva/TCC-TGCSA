// compile
// g++ -std=c++11 -g -O3 -DNDEBUG -I ~/include -L ~/lib example2.cpp -o program -lsdsl -ldivsufsort -ldivsufsort64

#include <sdsl/suffix_arrays.hpp>
#include <fstream>
#include <string>
#include <iostream>
#include <sdsl/vectors.hpp>

using namespace std;
using namespace sdsl;

// void print_suffixes(string originalString, csa_sada<> csa) {
//     cout << "Suffixes" << endl;
//     for (int i = 0; i < csa.size(); i++) {
//         int suffix_idx = csa[i];

//         int next = suffix_idx;

//         while (next < originalString.size()) {
//             cout << originalString[next];
//             next++;
//         }

//         cout << " $"  << endl;
//     }
//     cout << endl;
// }

// void csa_with_string() {
//     csa_sada<> csa;
//     string str = "1 2 3 7 1 4";
//     construct_im(csa, str, 'd');
//     print_suffixes(str, csa);
//     cout << "CSA: " << csa << endl;
//     cout << "size: " << csa.size() << endl;
//     cout << " i SA ISA PSI LF BWT   T[SA[i]..SA[i]-1]" << endl;
//     csXprintf(cout, "%2I %2S %3s %3P %2p %3B   %:3T", csa);
// }

void csa_with_int() {
    csa_sada<> csa;
    // construct(csa, "integers.sdsl");
    construct_im(csa, int_vector<>({1, 2, 3, 7, 1, 4}));
    // construct_im(csa, "1 2 3 7 1 4", 'd');
    // cout << "CSA: " << csa << endl;
    // cout << "size: " << csa.size() << endl;
    // cout << " i SA ISA PSI LF BWT   T[SA[i]..SA[i]-1]" << endl;
    // csXprintf(cout, "%2I %2S %3s %3P %2p %3B   %:3T", csa);
}

int main() {
    // csa_with_string();
    csa_with_int();
}