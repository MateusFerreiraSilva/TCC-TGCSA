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
        vector<uint> PsiRegular;
        vector<uint> Psi;
        Bitvector bitvector;

        uint mod(int a, int b) { // using this function bc in c++ -1 % 5 = 1, and should be -1 % 5 = 4
            const int r = a % b;

            return r < 0 ? r + b : r;
        }

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
            for (uint i = 0; i < sid.size(); i++) { // O^2, somatorio
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

        void buildPsiRegular() { // O^2 to build PSI, can i be better?
            for (uint i = 0; i < iCSA.size(); i++) {

                if (iCSA[i] == iCSA.size()) {
                        PsiRegular.push_back(1);
                        continue;
                }

                for (uint j = 0; j < iCSA.size(); j++) {
                    if (iCSA[j] == iCSA[i] + 1) {
                        const uint successorIdx = j + 1;
                        PsiRegular.push_back(successorIdx);
                        break;
                    }
                }
            }
        }

        void buildPsi() {
            const uint n = PsiRegular.size() / 4;
            for (uint i = 0; i < n * 3; i++) { // copy PsiRegular
                Psi.push_back(PsiRegular[i]);
            }

            for (uint i = n * 3; i < n * 4; i++) {
                Psi.push_back(mod((PsiRegular[i] - 2), n) + 1);
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
            puts("Bitvector:\n");
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

        void printCSA() {
            puts("iCSA:\n");
            for(auto it : iCSA) {
                printf("%2d", it);
                printf(" ");
            }
            puts("");
        }

        void printPsiRegular() {
            puts("Psi Regular:\n");
            for(auto it : PsiRegular) {
                printf("%2d", it);
                printf(" ");
            }
            puts("");
        }

        void printPsi() {
            puts("Psi:\n");
            for(auto it : Psi) {
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
            buildPsiRegular();
            buildPsi();
        }

        void print() {
            printSigma();
            printSigmaLine();
            printBitvector();
            printSid();
            printSuffixes();
            printCSA();
            printPsiRegular();
            printPsi();
        }
};

#endif