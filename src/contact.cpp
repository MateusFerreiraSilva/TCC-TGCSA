#include "contact.h"

Contact::Contact(uint u, uint v, uint ts, uint te) {
    this->u = u;
    this->v = v;
    this->ts = ts;
    this->te = te;
}

Contact::Contact(vector<uint> vec) {
    if (vec.size() != CONTACT_LENGTH) {
        throw invalid_argument("Invalid vector size");
    }

    u = vec[0];
    v = vec[1];
    ts = vec[2];
    te = vec[3];
}

bool Contact::operator <(const Contact & other) {
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

bool Contact::operator>(const Contact & other) {
    return !(this->operator<(other));
}

bool Contact::operator==(const Contact & other) {
    return u == other.u &&
        v == other.v &&
        ts == other.ts &&
        te == other.te;
}

void Contact::print() {
    printf("%2d %2d %2d %2d", u, v, ts, te);
}