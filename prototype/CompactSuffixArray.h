#ifndef COMPACT_SUFFIX_ARRAY
#define COMPACT_SUFFIX_ARRAY

#include <bits/stdc++.h>
#include "Bitvector.h"
#include "Contact.h"

using namespace std;


#define CONTACT_SIZE 4

class CompactSuffixArray {
    private:
        vector<Contact> sigma;

        void printSigma() {
            puts("Sigma:\n");
            for(auto contact : sigma) {
                contact.print();
                printf(" ");
            }
            puts("");
        }

    public:
        CompactSuffixArray(vector<Contact>& contacts) {
            sigma = contacts;
            sort(sigma.begin(), sigma.end());
        }

        void print() {
            printSigma();
        }
};

#endif