#ifndef SUFFIX
#define SUFFIX

#include <vector>
#include <sys/types.h>

using namespace std;

inline vector<uint> suffix_sequence; // global

class Suffix {
    public:
        uint idx;

        bool operator <(const Suffix& other);
        bool operator>(const Suffix& other);
        bool operator==(const Suffix& other);
};

#endif