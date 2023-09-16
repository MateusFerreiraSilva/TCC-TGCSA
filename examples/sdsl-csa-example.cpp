// compile
// g++ -std=c++11 -g -O3 -DNDEBUG -I ~/include -L ~/lib program.cpp -o program -lsdsl -ldivsufsort -ldivsufsort64

#include <sdsl/suffix_arrays.hpp>
#include <fstream>
#include <string>

using namespace sdsl;

typedef int_vector<>::size_type size_type;


int main() {
    std::string txt = "mississippi!";

    std::string first_pattern = "si";
    std::string second_pattern = "mi";
    size_type l_res, r_res;

    csa_sada<> csa;
    construct_im(csa, txt.c_str(), 1);
    std::cout << first_pattern << " occurs " << count(csa, first_pattern.c_str()) << " times.\n";
    std::cout << "CSA Size: " << csa.size() - 1 << "\n";
    std::cout << forward_search(csa, 0, csa.size() - 1, first_pattern.begin(), first_pattern.end(), l_res, r_res) << "\n";
    std::cout << forward_search(csa, 0, csa.size() - 1, second_pattern.begin(), second_pattern.end(), l_res, r_res) << "\n";


    store_to_file(csa,"fm_index-file.sdsl");
    std::ofstream out("fm_index-file.sdsl.html");
    write_structure<HTML_FORMAT>(csa,out);
}