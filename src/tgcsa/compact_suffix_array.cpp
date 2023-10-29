#include "compact_suffix_array.h"

uint CompactSuffixArray::mod(int a, int b) { // using this function bc in c++ -1 % 5 = 1, and should be -1 % 5 = 4
    const int r = a % b;

    return r < 0 ? r + b : r;
}

vector<Contact>* CompactSuffixArray::get_sequence_with_offset(const vector<Contact>& contacts, const vector<uint>& gaps) {
    vector<Contact>* contacts_with_offset = new vector<Contact>;
    contacts_with_offset->reserve(contacts.size());

    for (auto c : contacts) {
        c.u += gaps[(uint)ContactElementType::SrcVertex];
        c.v += gaps[(uint)ContactElementType::TargetVertex];
        c.ts += gaps[(uint)ContactElementType::StartingTime];
        c.te += gaps[(uint)ContactElementType::EndingTime];

        contacts_with_offset->push_back(c);
    }

    return contacts_with_offset;
}

vector<uint> CompactSuffixArray::get_S(const vector<uint>& sid) {
    set<uint> st;
    for (const auto& id : sid) {
        st.insert(id);
    }

    vector<uint> distinct_symbols(st.begin(), st.end());

    return distinct_symbols;
}

Bitvector CompactSuffixArray::get_bitvector_B(const vector<Contact>& contacts) {
    // get max value
    uint maxValue = 0;
    for (const auto& c : contacts) {
        maxValue = max(maxValue, c.te); // the max value will be te, because te are the greater values
    }

    Bitvector bitvector(maxValue);

    for (const auto& c : contacts) {
        bitvector.set(c.u);
        bitvector.set(c.v);
        bitvector.set(c.ts);
        bitvector.set(c.te);
    }

    return bitvector;
}

Bitvector CompactSuffixArray::get_bitvector_D(const vector<uint>& sid, const vector<uint>& A) {
    Bitvector bitvector(A.size());

    const uint first_idx = 0;

    if (A.size() >= 1) {
        bitvector.set(first_idx);
    }

    for (uint i = first_idx + 1; i < A.size(); i++) {
        const uint curr_value = sid[A[i] - 1];
        const uint prev_value = sid[A[i - 1] - 1];
        if (curr_value != prev_value) {
            bitvector.set(i);
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
    if (B.access(symbol) == 1) {
        return B.rank1(symbol);
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
    return B.select1(id);
}

vector<Suffix> CompactSuffixArray::get_suffixes(const vector<uint>& sequence) {
    suffix_sequence = sequence;
    vector<Suffix> suffixes(sequence.size());

    // iCSA need to be in base 1 because of the "$"
    for (uint i = 0; i < suffixes.size(); i++) {
        suffixes[i].idx = i + 1;
    }

    sort(suffixes.begin(), suffixes.end());

    return suffixes;
}

vector<uint>* CompactSuffixArray::get_psi_regular(const vector<uint>& A) {
    vector<uint>* psi_reg = new vector<uint>();
    psi_reg->reserve(A.size());

    map<uint, uint> values_to_indexes;
    for (uint i = 0; i < A.size(); i++) {
        values_to_indexes[A[i]] = i + 1; 
    }
    values_to_indexes[A.size() + 1] = 1;

    for (uint i = 0; i < A.size(); i++) {
        psi_reg->push_back(values_to_indexes[A[i] + 1]); 
    }

    return psi_reg;
}

vector<uint> CompactSuffixArray::get_psi(const vector<uint>& psi_reg) {
    vector<uint> psi;
    psi.reserve(psi_reg.size());
    
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

    for (const auto c : contacts) {
        maxVertice = max(max(maxVertice, c.u), max(maxVertice, c.v));
        maxTimestamp = max(max(maxTimestamp, c.ts), max(maxTimestamp, c.te));
    }

    const vector<uint> gaps { 0, maxVertice, maxVertice * 2, maxVertice * 2 + maxTimestamp };

    return gaps;
}

vector<uint>* CompactSuffixArray::get_sid(const vector<Contact>& contacts_with_offset) {
    vector<uint>* sid = new vector<uint>();
    sid->reserve(contacts_with_offset.size() * CONTACT_LENGTH);
    
    for (const auto& contact : contacts_with_offset) {
        sid->push_back(map_id(contact.u));
        sid->push_back(map_id(contact.v));
        sid->push_back(map_id(contact.ts));
        sid->push_back(map_id(contact.te));
    }

    return sid;
}

vector<uint>* CompactSuffixArray::get_iCSA(const vector<uint>& sequence) {
    vector<Suffix> suffixes = get_suffixes(sequence);

    vector<uint>* suffixes_idx = new vector<uint>();
    for (const auto& s : suffixes) {
        suffixes_idx->push_back(s.idx);
    }

    return suffixes_idx;
}

/**
 * Maps a symbol of the original sequence into sid
 * 
 * @param uint symbol of the original sequence.
 * @return `uint` value in sid
 */
uint CompactSuffixArray::get_map(uint symbol, ContactElementType type) {
    if ((uint)type >= gaps.size()) {
        stringstream stream;

        stream << "[CompactSuffixArray exception][get_map] invalid type: " << (uint)type << endl;

        throw invalid_argument(stream.str());
    }

    try {
        return B.rank1(symbol + gaps[(uint)type]);

    } catch(const invalid_argument& ex) {
        stringstream stream;

        stream << "[CompactSuffixArray exception][get_map] Element out of range, symbol: " << symbol << ", type:" << (uint)type << endl; 

        throw invalid_argument(stream.str());
    }
}


/**
 * Reverse Map a value of sid into the original symbol value
 * 
 * @param uint value of sid
 * @return `uint` original symbol value
 */
uint CompactSuffixArray::get_unmap(uint id, ContactElementType type) {
    if ((uint)type >= gaps.size()) {
        stringstream stream;

        stream << "[CompactSuffixArray exception][get_map] invalid type: " << (uint)type << endl;

        throw invalid_argument(stream.str());
    }

    return B.select1(id) - gaps[(uint)type];
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

        const uint sid_value = S[D.rank1(mid > 0 ? mid - 1 : 0) - 1];
        // const uint sid_value = S[D.rank1(mid - 1) - 1]; // Original

        if (id < sid_value) {
            r = mid > 0 ? mid - 1 : 0;
            // r = mid - 1; // original
        } else if (id > sid_value) {
            l = mid + 1;
        } else {
            idx = mid > 0 ? mid - 1 : 0;
            // idx = mid - 1; // original
            break;
        }
    }

    // idx is the index of the first result of a suffix that starts with symbol

    return get_suffix_range(idx);
}

pair<uint, uint> CompactSuffixArray::get_suffix_range(uint idx) {
    uint range_start = idx;
    uint range_end = idx;

    uint sid_value = S[D.rank1(idx) - 1];

    if (idx > 0) { // avoid seg fault
        for (uint i = idx - 1; i >= 0; i--) {
            uint left_sid = S[D.rank1(i) - 1];
            
        
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
            uint right_sid = S[D.rank1(i) - 1];

            if (sid_value != right_sid) {
                break;
            }

            range_end = i;
        }    
    }

    return make_pair(range_start, range_end);
}

void debug_print(bool debug_mode, const vector<Contact>& contacts, string name) {
    if (!debug_mode) {
        return;
    }

    name += ":";

    cout << name << endl;
    for (Contact it : contacts) {
        it.print();
    }
    cout << endl << endl;
}

void debug_print(bool debug_mode, Bitvector bitvector, string name) {
    if (!debug_mode) {
        return;
    }

    name += ":";

    cout << name << endl;
    bitvector.print();
    cout << endl << endl;
}

template <class T>
void debug_print(bool debug_mode, const vector<T>& vec, string name) {
    if (!debug_mode) {
        return;
    }

    name += ":";

    cout << name << endl;
    for (const T& it : vec) {
        cout << it << " ";
    }
    cout << endl << endl;
}

CompactSuffixArray::CompactSuffixArray() {}

CompactSuffixArray::CompactSuffixArray(vector<Contact>* contacts, const bool debug_mode) {
    debug_print(debug_mode, *contacts, "Contacts");
    
    gaps = get_gaps(*contacts);
    
    sort(contacts->begin(), contacts->end());
    debug_print(debug_mode, *contacts, "Sigma");

    vector<Contact>* contacts_with_offset = get_sequence_with_offset(*contacts, gaps);
    delete contacts;
    debug_print(debug_mode, *contacts_with_offset, "SigmaLine");

    B = get_bitvector_B(*contacts_with_offset);
    debug_print(debug_mode, B, "B (Bitvector)");


    // sequence of id without gaps in the alphabet, ids to sigma array
    vector<uint>* sid = get_sid(*contacts_with_offset);
    delete contacts_with_offset;
    sequence_size = sid->size();
    debug_print(debug_mode, *sid, "Sid");

    S = get_S(*sid);
    debug_print(debug_mode, S, "S (Distinct Symbols)");

    // iCSA of sid
    vector<uint>* A = get_iCSA(*sid);
    debug_print(debug_mode, *A, "A (Suffix Array - iCSA)");

    D = get_bitvector_D(*sid, *A);
    delete sid;
    debug_print(debug_mode, D, "D (Bitvector)");

    vector<uint>* psi_reg = get_psi_regular(*A);
    delete A;
    debug_print(debug_mode, *psi_reg, "Psi Regular");

    psi = get_psi(*psi_reg);
    delete psi_reg;
    debug_print(debug_mode, psi, "Psi");
}