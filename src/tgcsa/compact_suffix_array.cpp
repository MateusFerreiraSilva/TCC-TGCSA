#include "compact_suffix_array.h"

uint CompactSuffixArray::mod(int a, int b) { // using this function bc in c++ -1 % 5 = 1, and should be -1 % 5 = 4
    const int r = a % b;

    return r < 0 ? r + b : r;
}

vector<Contact> CompactSuffixArray::get_sequence_with_offset(const vector<Contact>& contacts) {
    vector<Contact> contactsWithOffset;

    for (auto c : contacts) {
        c.u += gaps[(uint)ContactElementType::SrcVertex];
        c.v += gaps[(uint)ContactElementType::TargetVertex];
        c.ts += gaps[(uint)ContactElementType::StartingTime];
        c.te += gaps[(uint)ContactElementType::EndingTime];

        contactsWithOffset.push_back(c);
    }

    return contactsWithOffset;
}

vector<uint> CompactSuffixArray::get_S() {
    set<uint> st;
    for (auto id : sid) {
        st.insert(id);
    }

    vector<uint> distinct_symbols(st.begin(), st.end());

    return distinct_symbols;
}

Bitvector* CompactSuffixArray::get_bitvector_B(const vector<Contact>& contacts) {
    // get max value
    uint maxValue = 0;
    for (auto c : contacts) {
        maxValue = max(maxValue, c.te); // the max value will be te, because te are the greater values
    }

    Bitvector *bitvector = new Bitvector(maxValue);

    for (auto c : contacts) {
        bitvector->set(c.u);
        bitvector->set(c.v);
        bitvector->set(c.ts);
        bitvector->set(c.te);
    }

    return bitvector;
}

Bitvector* CompactSuffixArray::get_bitvector_D() {
    Bitvector *bitvector = new Bitvector(A.size());

    const uint first_idx = 0;

    if (A.size() >= 1) {
        bitvector->set(first_idx);
    }

    for (uint i = first_idx + 1; i < A.size(); i++) {
        const uint curr_value = sid[A[i] - 1];
        const uint prev_value = sid[A[i - 1] - 1];
        if (curr_value != prev_value) {
            bitvector->set(i);
        }
    }

    return bitvector;
}

/**
 * Get the id of the where original symbol without offset is present
 * 
 * @param uint value of contacts_with_offset.
 * @return `uint` the id of the corresponding element on the original sequece: array sigma
 */
uint CompactSuffixArray::map_id(uint symbol) {
    if (B->access(symbol) == 1) {
        return B->rank1(symbol);
    }

    return 0;
}

/**
 * Get value int the sequence with offset contacts_with_offset
 * 
 * @param uint id in the original sequence: sigma.
 * @return `uint` corresponding value in contacts_with_offset
 */
uint CompactSuffixArray::unmap_id(uint id) {
    return B->select1(id);
}

/* O^2 to build PSI, can i be better? */
vector<pair<vector<uint>, uint>> CompactSuffixArray::get_suffixes_and_indexes(const vector<uint>& sequence) {
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

    return suffixes_and_indexes;
}

vector<vector<uint>> CompactSuffixArray::get_suffixes(const vector<pair<vector<uint>, uint>>&  suffixes_and_indexes) {
    vector<vector<uint>> suffixes;
    
    for (auto it : suffixes_and_indexes) {
        suffixes.push_back(it.first);
    }

    return suffixes;
}

vector<uint> CompactSuffixArray::get_psi_regular(const vector<uint>& A) { // O^2 to build PSI, can i be better?
    vector<uint> psi_reg;
    
    for (uint i = 0; i < A.size(); i++) {

        if (A[i] == A.size()) {
                psi_reg.push_back(1);
                continue;
        }

        for (uint j = 0; j < A.size(); j++) {
            if (A[j] == A[i] + 1) {
                const uint successorIdx = j + 1;
                psi_reg.push_back(successorIdx);
                break;
            }
        }
    }

    return psi_reg;
}

vector<uint> CompactSuffixArray::get_psi(const vector<uint>& psi_reg) {
    vector<uint> psi;
    
    const uint n = psi_reg.size() / 4;

    for (uint i = 0; i < n * 3; i++) { // copy PsiRegular
        psi.push_back(psi_reg[i]);
    }

    for (uint i = n * 3; i < n * 4; i++) {
        psi.push_back(mod((psi_reg[i] - 2), n) + 1);
    }

    return psi;
}

/*
 * returns an array with the "offsets"
*/
vector<uint> CompactSuffixArray::get_gaps(const vector<Contact>& contacts) {
    
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

vector<uint> CompactSuffixArray::get_sid(const vector<Contact>& contacts_with_offset) {
    vector<uint> sid;
    
    for (auto contact : contacts_with_offset) {
        sid.push_back(map_id(contact.u));
        sid.push_back(map_id(contact.v));
        sid.push_back(map_id(contact.ts));
        sid.push_back(map_id(contact.te));
    }

    return sid;
}

vector<uint> CompactSuffixArray::get_iCSA(const vector<uint>& sequence) {
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
uint CompactSuffixArray::get_map(uint symbol, ContactElementType type) {
    if ((uint)type >= gaps.size()) {
        throw invalid_argument("invalid type");
    }

    return B->rank1(symbol + gaps[(uint)type]);
}


/**
 * Reverse Map a value of sid into the original symbol value
 * 
 * @param uint value of sid
 * @return `uint` original symbol value
 */
uint CompactSuffixArray::get_unmap(uint id, ContactElementType type) {
    if ((uint)type >= gaps.size()) {
        throw invalid_argument("invalid type");
    }

    return B->select1(id) - gaps[(uint)type];
}

/**
 * Gets the indexes in A where the pattern occurs
 * 
 * @param uint id
 * @return `pair<uint, pair>` range it the index [start, end]
 */
pair<uint, uint> CompactSuffixArray::CSA_binary_search(uint id) { // TO DO, what happens if we dont find the id?
    uint idx;
    uint l = 0, mid, r = sequence_size - 1;

    while (l <= r) {
        mid = l + (r - l) / 2;

        const uint sid_value = S[D->rank1(mid - 1) - 1];

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

    uint sid_value = S[D->rank1(idx) - 1];

    if (idx > 0) { // avoid seg fault
        for (uint i = idx - 1; i >= 0; i--) {
            uint left_sid = S[D->rank1(i) - 1];
            
        
            if (sid_value != left_sid) {
                break;
            }

            range_start = i;

            if (i == 0) {
                break; // avoid seg fault because of uint
            }
        }
    }

    if (idx < sequence_size) {
        for (uint i = idx + 1; i < sequence_size; i++) {
            uint right_sid = S[D->rank1(i) - 1];

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
    for(auto c : contacts) {
        c.print();
        printf(" ");
    }
    puts("\n");
    
    puts("Sigma Line:\n");
    for(auto contact : contacts_with_offset) {
        contact.print();
        printf(" ");
    }
    puts("\n");

    puts("B:\n");
    B->print();
    puts("\n");

    puts("Sid:\n");
    for(auto it : sid) {
        printf("%2u", it);
        printf(" ");
    }
    puts("\n");

    puts("A:\n");
    for(auto it : A) {
        printf("%2u", it);
        printf(" ");
    }
    puts("\n");

    puts("D:\n");
    D->print();
    puts("\n");

    puts("S:\n");
    for(auto it : S) {
        printf("%2u", it);
        printf(" ");
    }
    puts("\n");

    puts("Psi Reg:\n");
    for(auto it : psi_reg) {
        printf("%2u", it);
        printf(" ");
    }
    puts("\n");

    puts("Psi:\n");
    for(auto it : psi) {
        printf("%2u", it);
        printf(" ");
    }
    puts("");
}

CompactSuffixArray::CompactSuffixArray(const vector<Contact>& contacts, const bool debug_mode) {
    copy(contacts.begin(), contacts.end(), back_inserter(this->contacts));
    gaps = get_gaps(this->contacts);
    sort(this->contacts.begin(), this->contacts.end());
    contacts_with_offset = get_sequence_with_offset(this->contacts);
    B = get_bitvector_B(contacts_with_offset);
    sid = get_sid(contacts_with_offset);
    sequence_size = sid.size();
    S = get_S();
    A = get_iCSA(sid);
    D = get_bitvector_D();
    psi_reg = get_psi_regular(A);
    psi = get_psi(psi_reg);

    if (!debug_mode) {
        contacts_with_offset.clear();
        sid.clear();
        A.clear();
        psi_reg.clear();
    }
}