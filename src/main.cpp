#include <bits/stdc++.h>
#include "tgcsa/compact_suffix_array.h"

using namespace std;

void testBitvector() {
    Bitvector bitvector(64);

    bitvector.set(0);
    bitvector.set(4);
    bitvector.flip(12);

    bitvector.print();

    printf("rank %u: %u\n", 4, bitvector.rank1(4));
    printf("rank %u: %u\n", 5, bitvector.rank1(5));
    printf("rank %u: %u\n", 12, bitvector.rank1(12));
    printf("rank %u: %u\n", 19, bitvector.rank1(19));

    printf("select %u: %u\n", 1, bitvector.select1(1));
    printf("select %u: %u\n", 2, bitvector.select1(2));
    printf("select %u: %u\n", 3, bitvector.select1(3));
}

void printContacts(vector<Contact> contacts) {
    puts("Contacts:\n");
    for(auto c : contacts) {
        c.print();
        printf(" ");
    }
    puts("");
}

void testCSA() {
    vector<Contact> contacts {
        Contact(1, 10, 15, 17),
        Contact(1, 3, 13, 17),
        Contact(5, 6, 8, 9),
        Contact(1, 3, 13, 14)
    };

    printContacts(contacts);

    CompactSuffixArray csa(contacts);


    csa.print();
}

void bookExample() {
    vector<Contact> contacts {
        Contact(1, 3, 1, 8),
        Contact(1, 4, 5, 8),
        Contact(2, 1, 1, 5),
        Contact(4, 3, 7, 8),
        Contact(4, 5, 5, 7)
    };

    printContacts(contacts);

    CompactSuffixArray csa(contacts);

    csa.print();
}

vector<string> get_args(int argc, char* argv[]) {
    vector<string> args;
    
    for (uint i = 0; i < argc; i++) {
        args.push_back(argv[i]);
    }

    return args;
}

map<string, bool> get_execution_parameters(int argc, char* argv[]) {
    vector<string> args = get_args(argc, argv);

    map<string, bool> execution_parameters = {
        { "debug", (find(args.begin(), args.end(), "--debug") != args.end()) }
    };

    return execution_parameters;
}


int main(int argc, char* argv[]) {
    auto parameters = get_execution_parameters(argc, argv);

    if (parameters["debug"]) {
        bookExample();
    }

    return 0;
}