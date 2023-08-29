// compile
// g++ -std=c++11 -O3 -DNDEBUG -I ~/include -L ~/lib program.cpp -o program -lsdsl -ldivsufsort -ldivsufsort64

#include <sdsl/suffix_arrays.hpp>
#include <fstream>

using namespace sdsl;

int main() {
    csa_wt<> fm_index;
    construct_im(fm_index, "mississippi!", 1);
    std::cout << "'si' occurs " << count(fm_index,"si") << " times.\n";
    store_to_file(fm_index,"fm_index-file.sdsl");
    std::ofstream out("fm_index-file.sdsl.html");
    write_structure<HTML_FORMAT>(fm_index,out);
}