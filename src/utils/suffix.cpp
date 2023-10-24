#include "suffix.h"

bool Suffix::operator <(const Suffix& other) {
    uint i = idx - 1, j = other.idx - 1;
    while (i < suffix_sequence.size() && j < suffix_sequence.size()) {
        if (suffix_sequence[i] < suffix_sequence[j]) {
            return true;
        } else if (suffix_sequence[i] > suffix_sequence[j]) {
            return false;
        }

        i++;
        j++;
    }

    return i == suffix_sequence.size() - 1;
}

bool Suffix::operator>(const Suffix& other) {
    return !(this->operator<(other));
}

bool Suffix::operator==(const Suffix& other) {
    return idx == other.idx;
}