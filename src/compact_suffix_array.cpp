#include "compact_suffix_array.h"

// private

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

uint CompactSuffixArray::mapId(uint id) {
    if (bitvector.access(id) == 1) {
        return bitvector.rank1(id);
    }

    return 0;
}

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

void CompactSuffixArray::printSigma() {
    puts("Sigma:\n");
    for(auto contact : sigma) {
        contact.print();
        printf(" ");
    }
    puts("");
}

void CompactSuffixArray::printSigmaLine() {
    puts("SigmaLine:\n");
    for(auto contact : sigmaLine) {
        contact.print();
        printf(" ");
    }
    puts("");
}


void CompactSuffixArray::printBitvector() {
    puts("Bitvector:\n");
    bitvector.print();
    puts("");
}

void CompactSuffixArray::printSid() {
    puts("sid:\n");
    for(auto it : sid) {
        printf("%2d", it);
        printf(" ");
    }
    puts("");
}

void CompactSuffixArray::printSuffixes() {
    puts("Suffixes:\n");
    for(auto suffix : suffixes) {
        for (auto it : suffix) {
            printf("%2d", it);
            printf(" ");
        }
        puts("");
    }
    puts("");
}

void CompactSuffixArray::printCSA() {
    puts("iCSA:\n");
    for(auto it : iCSA) {
        printf("%2d", it);
        printf(" ");
    }
    puts("");
}

void CompactSuffixArray::printPsiRegular() {
    puts("Psi Regular:\n");
    for(auto it : PsiRegular) {
        printf("%2d", it);
        printf(" ");
    }
    puts("");
}

void CompactSuffixArray::printPsi() {
    puts("Psi:\n");
    for(auto it : Psi) {
        printf("%2d", it);
        printf(" ");
    }
    puts("");
}

// public:

CompactSuffixArray::CompactSuffixArray(vector<Contact> & contacts) {
    sigma = contacts;
    gaps = get_gaps(contacts);
    sort(sigma.begin(), sigma.end());
    sigmaLine = addOffsetToTheSequence(sigma);
    initializeBitvector(sigmaLine);
    sid = get_sid(sigmaLine);
    iCSA = get_iCSA(sid);
    PsiRegular = get_psi_regular(iCSA);
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
        sid.push_back(mapId(contact.u));
        sid.push_back(mapId(contact.v));
        sid.push_back(mapId(contact.ts));
        sid.push_back(mapId(contact.te));
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

uint CompactSuffixArray::get_map(uint symbol, unsigned char type) {
    if (type >= gaps.size()) {
        throw invalid_argument("invalid type");
    }

    return bitvector.rank1(symbol + gaps[type]);
}

uint CompactSuffixArray::get_unmap(uint symbol, unsigned char type) {
    if (type >= gaps.size()) {
        throw invalid_argument("invalid type");
    }

    return bitvector.select1(symbol) - gaps[type];
}

void CompactSuffixArray::print() {
    printSigma();
    printSigmaLine();
    printBitvector();
    printSid();
    printSuffixes();
    printCSA();
    printPsiRegular();
    printPsi();
}