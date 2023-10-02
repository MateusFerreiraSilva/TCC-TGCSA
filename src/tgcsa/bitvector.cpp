#include "bitvector.h"

void Bitvector::validateIdx(uint idx) {
    if (idx >= bs.size()) {
        throw invalid_argument("Element out of range");
    }
}

uint Bitvector::select(uint idx, uint type) {
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

void Bitvector::print() {
    cout << bs << endl;
}

string Bitvector::to_string() {
    return bs.to_string();
}

uint Bitvector::access(uint idx) {
    validateIdx(idx);

    return bs[idx];
}

void Bitvector::set(uint idx) {
    validateIdx(idx);

    bs[idx] = 1;
}

void Bitvector::unset(uint idx) {
    validateIdx(idx);

    bs[idx] = 1;
}

void Bitvector::flip(uint idx) {
    validateIdx(idx);

    bs[idx] = !bs[idx];
}

uint Bitvector::rank1(uint idx) {
    validateIdx(idx);

    uint count = 0;

    for (uint i = 0; i <= idx; i++) {
        if (bs[i] == 1) {
            count++;
        }
    }

    return count;
}

uint Bitvector::rank0(uint idx) {
    validateIdx(idx);

    return idx - rank1(idx);
}

uint Bitvector::select1(uint idx) {
    return select(idx, 1);
}

uint Bitvector::select0(uint idx) {
    return select(idx, 0);
}