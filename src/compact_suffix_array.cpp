#include "compact_suffix_array.h"

uint CompactSuffixArray::mod(int a, int b) { // using this function bc in c++ -1 % 5 = 1, and should be -1 % 5 = 4
    const int r = a % b;

    return r < 0 ? r + b : r;
}

vector<Contact> CompactSuffixArray::addOffsetToTheSequence(vector<Contact> & contacts) {
    
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

void CompactSuffixArray::initializeBitvector(vector<Contact> & contacts) {
    for (auto c : contacts) {
        bitvector.set(c.u);
        bitvector.set(c.v);
        bitvector.set(c.ts);
        bitvector.set(c.te);
    }
}

/**
 * Get the id of the where original symbol without offset is present
 * 
 * @param uint value of sigmaLine.
 * @return `uint` the id of the corresponding element on the original sequece: array sigma
 */
uint CompactSuffixArray::map_id(uint symbol) {
    if (bitvector.access(symbol) == 1) {
        return bitvector.rank1(symbol);
    }

    return 0;
}

/**
 * Get value int the sequence with offset sigmaLine
 * 
 * @param uint id in the original sequence: sigma.
 * @return `uint` corresponding value in sigmaLine
 */
uint CompactSuffixArray::unmap_id(uint id) {
    return bitvector.select1(id);
}

/* O^2 to build PSI, can i be better? */
vector<pair<vector<uint>, uint>> CompactSuffixArray::get_suffixes_and_indexes(vector<uint> sequence) {
    vector<vector<uint>> suffixes;
    
    for (uint i = 0; i < sequence.size(); i++) { // O^2, somatorio
        suffixes.push_back(vector<uint>());
        for (uint j = i; j < sequence.size(); j++) {
            suffixes[i].push_back(sequence[j]);
        }
    }

    vector<pair<vector<uint>, uint>> suffixes_and_indexes;
    for (uint i = 0; i < suffixes.size(); i++) {
        suffixes_and_indexes.push_back(make_pair(suffixes[i], i + 1));
        // iCSA need to be in base 1 because of the "$"
    }

    sort(suffixes_and_indexes.begin(), suffixes_and_indexes.end());

    this->suffixes_and_indexes = suffixes_and_indexes; // TO DO remove

    return suffixes_and_indexes;
}

vector<vector<uint>> CompactSuffixArray::get_suffixes(vector<pair<vector<uint>, uint>>  suffixes_and_indexes) {
    vector<vector<uint>> suffixes;
    
    for (auto it : suffixes_and_indexes) {
        suffixes.push_back(it.first);
    }

    this->suffixes = suffixes; // TO DO remove

    return suffixes;
}

vector<uint> CompactSuffixArray::get_psi_regular(vector<uint> iCSA) { // O^2 to build PSI, can i be better?
    vector<uint> PsiRegular;
    
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

    return PsiRegular;
}

vector<uint> CompactSuffixArray::get_psi(vector<uint> PsiRegular) {
    vector<uint> Psi;
    
    const uint n = PsiRegular.size() / 4;

    for (uint i = 0; i < n * 3; i++) { // copy PsiRegular
        Psi.push_back(PsiRegular[i]);
    }

    for (uint i = n * 3; i < n * 4; i++) {
        Psi.push_back(mod((PsiRegular[i] - 2), n) + 1);
    }

    return Psi;
}

CompactSuffixArray::CompactSuffixArray(vector<Contact> & contacts) {
    sigma = contacts;
    gaps = get_gaps(contacts);
    sort(sigma.begin(), sigma.end());
    sigmaLine = addOffsetToTheSequence(sigma);
    initializeBitvector(sigmaLine);
    sid = get_sid(sigmaLine);
    A = get_iCSA(sid);
    PsiRegular = get_psi_regular(A);
    Psi = get_psi(PsiRegular);
}

/*
 * returns an array with the "offsets"
*/
vector<uint> CompactSuffixArray::get_gaps(vector<Contact>& contacts) {
    
    uint maxVertice = 0, maxTimestamp = 0;

    for (auto c : contacts) {
        maxVertice = max(max(maxVertice, c.u), max(maxVertice, c.v));
        maxTimestamp = max(max(maxTimestamp, c.ts), max(maxTimestamp, c.te));
    }

    vector<uint> gaps = vector<uint>(CONTACT_LENGTH);

    gaps[0] = 0;
    gaps[1] = maxVertice;
    gaps[2] = maxVertice * 2;
    gaps[3] = maxVertice * 2 + maxTimestamp;

    return gaps;
}

vector<uint> CompactSuffixArray::get_sid(vector<Contact> sigmaLine) {
    vector<uint> sid;
    
    for (auto contact : sigmaLine) {
        sid.push_back(map_id(contact.u));
        sid.push_back(map_id(contact.v));
        sid.push_back(map_id(contact.ts));
        sid.push_back(map_id(contact.te));
    }

    return sid;
}

vector<uint> CompactSuffixArray::get_iCSA(vector<uint> sequence) {
    vector<pair<vector<uint>, uint>>suffixes_and_indexes = get_suffixes_and_indexes(sequence);
    
    vector<uint> iCSA;
    for (auto it : suffixes_and_indexes) {
        iCSA.push_back(it.second);
    }

    return iCSA;
}

/**
 * Maps a symbol of the original sequence into sid
 * 
 * @param uint symbol of the original sequence.
 * @return `uint` value in sid
 */
uint CompactSuffixArray::get_map(uint symbol, unsigned char type) {
    if (type >= gaps.size()) {
        throw invalid_argument("invalid type");
    }

    return bitvector.rank1(symbol + gaps[type]);
}


/**
 * Reverse Map a value of sid into the original symbol value
 * 
 * @param uint value of sid
 * @return `uint` original symbol value
 */
uint CompactSuffixArray::get_unmap(uint id, unsigned char type) {
    if (type >= gaps.size()) {
        throw invalid_argument("invalid type");
    }

    return bitvector.select1(id) - gaps[type];
}

pair<uint, uint> CompactSuffixArray::CSA_binary_search(uint id) {
    uint idx;
    uint l = 1, mid, r = A.size();

    while (l <= r) {
        mid = l + (r - l) / 2;

        uint sid_idx = A[mid - 1];
        uint sid_value = sid[sid_idx - 1];

        if (id < sid_value) {
            r = mid - 1;
        } else if (id > sid_value) {
            l = mid + 1;
        } else {
            idx = mid - 1;
            break;
        }
    }

    // idx is the index of the first result of a suffix that starts with symbol

    return get_suffix_range(idx);
}

pair<uint, uint> CompactSuffixArray::get_suffix_range(uint idx) {
    uint range_start = idx;
    uint range_end = idx;

    uint sid_value = sid[A[idx]- 1];

    if (idx > 0) { // avoid seg fault
        for (uint i = idx - 1; i >= 0; i--) {
            uint left_sid = sid[A[i]- 1];
        
            if (sid_value != left_sid) {
                break;
            }

            range_start = i;

            if (i == 0) {
                break; // avoid seg fault because of uint
            }
        }
    }

    if (idx < sid.size()) {
        for (uint i = idx + 1; i < sid.size(); i++) {
            uint right_sid = sid[A[i] - 1];

            if (sid_value != right_sid) {
                break;
            }

            range_end = i;
        }    
    }

    return make_pair(range_start, range_end);
}

void CompactSuffixArray::print() {
    puts("Sigma:\n");
    for(auto contact : sigma) {
        contact.print();
        printf(" ");
    }
    puts("");
    
    puts("SigmaLine:\n");
    for(auto contact : sigmaLine) {
        contact.print();
        printf(" ");
    }
    puts("");

    puts("Bitvector:\n");
    bitvector.print();
    puts("");

    puts("Sid:\n");
    for(auto it : sid) {
        printf("%2d", it);
        printf(" ");
    }
    puts("");

    puts("Suffixes:\n");
    for(auto suffix : suffixes) {
        for (auto it : suffix) {
            printf("%2d", it);
            printf(" ");
        }
        puts("");
    }
    puts("");

    puts("iCSA:\n");
    for(auto it : A) {
        printf("%2d", it);
        printf(" ");
    }
    puts("");

    puts("Psi Regular:\n");
    for(auto it : PsiRegular) {
        printf("%2d", it);
        printf(" ");
    }
    puts("");

    puts("Psi:\n");
    for(auto it : Psi) {
        printf("%2d", it);
        printf(" ");
    }
    puts("");
}