#ifndef CONTACT
#define CONTACT

#include <bits/stdc++.h>

using namespace std;


#define CONTACT_SIZE 4

class Contact {
    public:
        uint u, v, ts, te;

        Contact(uint u, uint v, uint ts, uint te) {
            this->u = u;
            this->v = v;
            this->ts = ts;
            this->te = te;
        }

        Contact(vector<uint> vec) {
            if (vec.size() != CONTACT_SIZE) {
                throw invalid_argument("Invalid vector size");
            }

            u = vec[0];
            v = vec[1];
            ts = vec[2];
            te = vec[3];
        }

        bool operator <(const Contact & other) {
            if (u < other.u) {
                return true;
            } else if (u == other.u) {
                if (v < other.v) {
                    return true;
                } else if (v == other.v) {
                    if (ts < other.ts) {
                        return true;
                    } else if (ts == other.ts) {
                        return te <= other.te;
                    }
                }
            }

            return false;
        }

        bool operator>(const Contact & other) {
            return !(this->operator<(other));
        }

        bool operator==(const Contact & other) {
            return u == other.u &&
                v == other.v &&
                ts == other.ts &&
                te == other.te;
        }

        void print() {
            printf("%2d %2d %2d %2d", u, v, ts, te);
        }
};

#endif