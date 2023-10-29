#ifndef CONTACT
#define CONTACT

#include <sys/types.h>
#include <stdio.h>
#include <vector>
#include <stdexcept>
	
using namespace std;

#define CONTACT_LENGTH 4

class Contact {
    public:
        uint u, v, ts, te;

        Contact(uint u, uint v, uint ts, uint te);
        Contact(vector<uint> vec);
        bool operator <(const Contact& other);
        bool operator>(const Contact& other);
        bool operator==(const Contact& other);
        void print();
};

#endif