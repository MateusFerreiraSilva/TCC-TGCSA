#ifndef COMPACT_SUFFIX_ARRAY
#define COMPACT_SUFFIX_ARRAY

#include <bits/stdc++.h>
#include "Bitvector.h"
#include "Contact.h"

using namespace std;

#define CONTACT_LENGTH 4

class CompactSuffixArray {
    private:
        vector<uint> gaps = vector<uint>(CONTACT_LENGTH);
        vector<Contact> sigma;
        vector<Contact> sigmaLine;
        vector<uint> Sid;
        Bitvector bitvector;


        void initialzeGapsArray(vector<Contact>& contacts) {
            
            uint maxVertice = 0, maxTimestamp = 0;

            for (auto c : contacts) {
                maxVertice = max(max(maxVertice, c.u), max(maxVertice, c.v));
                maxTimestamp = max(max(maxTimestamp, c.ts), max(maxTimestamp, c.te));
            }

            gaps[0] = 0;
            gaps[1] = maxVertice;
            gaps[2] = maxVertice * 2;
            gaps[3] = maxVertice * 2 + maxTimestamp;
        }

        vector<Contact> addOffsetToTheSequence(vector<Contact> & contacts) {
            
            vector<Contact> contactsWithOffset;

            for (auto c : contacts) {
                c.u += gaps[0];
                c.v += gaps[1];
                c.ts += gaps[2];
                c.te += gaps[3];

                contactsWithOffset.push_back(c);
            }

            return contactsWithOffset;
        }

        void initializeBitvector(vector<Contact> & contacts) {
            for (auto c : contacts) {
                bitvector.set(c.u);
                bitvector.set(c.v);
                bitvector.set(c.ts);
                bitvector.set(c.te);
            }
        }

        uint mapId(uint id) {
            if (bitvector.access(id) == 1) {
                return bitvector.rank1(id);
            }

            return 0;
        }

        void initializeSid() {
            for (auto contact : sigmaLine) {
                Sid.push_back(mapId(contact.u));
                Sid.push_back(mapId(contact.v));
                Sid.push_back(mapId(contact.ts));
                Sid.push_back(mapId(contact.te));
            }
        }


        void printSigma() {
            puts("Sigma:\n");
            for(auto contact : sigma) {
                contact.print();
                printf(" ");
            }
            puts("");
        }

        void printSigmaLine() {
            puts("SigmaLine:\n");
            for(auto contact : sigmaLine) {
                contact.print();
                printf(" ");
            }
            puts("");
        }


        void printBitvector() {
            puts("Bitvevtor:\n");
            bitvector.print();
            puts("");
        }

        void printSid() {
            puts("Sid:\n");
            for(auto it : Sid) {
                printf("%2d", it);
                printf(" ");
            }
            puts("");
        }

    public:
        CompactSuffixArray(vector<Contact> & contacts) {
            sigma = contacts;
            initialzeGapsArray(contacts);
            sort(sigma.begin(), sigma.end());
            sigmaLine = addOffsetToTheSequence(sigma);
            initializeBitvector(sigmaLine);
            initializeSid();
        }

        void print() {
            printSigma();
            printSigmaLine();
            printBitvector();
            printSid();
        }
};

#endif