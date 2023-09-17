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
        vector<uint> sid;
        vector<vector<uint>> suffixes;
        vector<uint> iCSA;
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

        void initializesid() {
            for (auto contact : sigmaLine) {
                sid.push_back(mapId(contact.u));
                sid.push_back(mapId(contact.v));
                sid.push_back(mapId(contact.ts));
                sid.push_back(mapId(contact.te));
            }
        }

        void buildCSA() {
            for (uint i = 0; i < sid.size(); i++) {
                suffixes.push_back(vector<uint>());
                for (uint j = i; j < sid.size(); j++) {
                    suffixes[i].push_back(sid[j]);
                }
            }

            vector<pair<vector<uint>, uint>> suffixes_and_indexes;
            for (uint i = 0; i < suffixes.size(); i++) {
                suffixes_and_indexes.push_back(make_pair(suffixes[i], i + 1));
                // iCSA need to be in base 1 because of the "$"
            }

            sort(suffixes_and_indexes.begin(), suffixes_and_indexes.end());

            for (auto s : suffixes_and_indexes) {
                iCSA.push_back(s.second);
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
            puts("sid:\n");
            for(auto it : sid) {
                printf("%2d", it);
                printf(" ");
            }
            puts("");
        }

        void printSuffixes() {
            puts("Suffixes:\n");
            for(auto suffix : suffixes) {
                for (auto it : suffix) {
                    printf("%2d", it);
                    printf(" ");
                }
                puts("");
            }
            puts("");
        }

        void printiCSA() {
            puts("iCSA:\n");
            for(auto it : iCSA) {
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
            initializesid();
            buildCSA();
        }

        void print() {
            printSigma();
            printSigmaLine();
            printBitvector();
            printSid();
            printSuffixes();
            printiCSA();
        }
};

#endif