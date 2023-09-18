#ifndef BITVECTOR
#define BITVECTOR

#include <bits/stdc++.h>

using namespace std;

#define BITSET_MAX_SIZE_TEST 20
#define BITSET_MAX_SIZE 64

class Bitvector {
    private:
        // bitset<BITSET_MAX_SIZE_TEST> bs;
        bitset<BITSET_MAX_SIZE> bs;

        void validateIdx(uint idx) {
            if (idx >= bs.size()) {
                throw invalid_argument("Element out of range");
            }
        }

        uint select(uint idx, uint type) {
            for (uint it = 0, count = 0; it < bs.size(); it++) {
                if (bs[it] == type) {
                    count++;
                }

                if (count == idx) {
                    return it;
                }
            }

            throw invalid_argument("Not found");
        }

    public:
        void print() {
            cout << bs << endl;
        }

        uint access(uint idx) {
            validateIdx(idx);

            return bs[idx];
        }

        void set(uint idx) {
            validateIdx(idx);

            bs[idx] = 1;
        }

        void unset(uint idx) {
            validateIdx(idx);

            bs[idx] = 1;
        }

        void flip(uint idx) {
            validateIdx(idx);

            bs[idx] = !bs[idx];
        }

        uint rank1(uint idx) {
            validateIdx(idx);

            uint count = 0;

            for (uint i = 0; i <= idx; i++) {
                if (bs[i] == 1) {
                    count++;
                }
            }

            return count;
        }

        uint rank0(uint idx) {
            validateIdx(idx);

            return bs.size() - rank1(idx);
        }

        uint select1(uint idx) {
            return select(idx, 1);
        }

        uint select0(uint idx) {
            return select(idx, 0);
        }
};

#endif