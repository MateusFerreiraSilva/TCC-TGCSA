#include "tgcsa.h"

TGCSA::TGCSA(vector<Contact>& contacts, const bool debug_mode) {
    csa = new CompactSuffixArray(contacts, debug_mode);
}

/**
 * Gets the direct neighbors of a given vrtx in a given time, where t1 < time < t2
 * 
 * @param uint src vrtx
 * @param uint time
 * @return `vector<uint>` neighbors 
 */
vector<uint> TGCSA::direct_neighbors(uint vrtx, uint time) {
    vector<uint> neighbors;

    uint src_vrtx = csa->get_map(vrtx, ContactElementType::SrcVertex);
    
    if (src_vrtx == 0) { // TO DO, check when this will happen? Should happen when we pass a value out of the range. 
        return neighbors; // vrtx does not appears as a source vertex
    }

    uint starting_time = csa->get_map(time, ContactElementType::StartingTime);
    uint ending_time = csa->get_map(time, ContactElementType::EndingTime);

    uint lu, ru; // range A[lu, ru] for vertex u
    uint lts, rts; // range A[lts, rts] for starting time ts
    uint lte, rte; // range A[lte, rte] for ending time te

    tie(lu, ru) = csa->CSA_binary_search(src_vrtx);
    tie(lts, rts) = csa->CSA_binary_search(starting_time);
    tie(lte, rte) = csa->CSA_binary_search(ending_time);

    for (uint i = lu; i <= ru; i++) {
        uint x = csa->psi[i]; // x = position of target vertex
        uint y = csa->psi[x - 1]; // y = position of starting time
        if (y - 1 <= rts) {
            uint z = csa->psi[y - 1]; // z = position of ending time
            if (z - 1 > rte) {
                // neighbors.push_back(get_unmap(x, ContactElementType::TargetVertex));
                neighbors.push_back(csa->get_unmap(csa->S[csa->D->rank1(x - 1) - 1], ContactElementType::TargetVertex));
            }
        }
    }

    return neighbors;
}

/**
 * Gets the reverse neighbors of a given vrtx in a given time, where t1 < time < t2
 * 
 * @param uint target vrtx
 * @param uint time
 * @return `vector<uint>` neighbors 
 */
vector<uint> TGCSA::reverse_neighbors(uint vrtx, uint time) {
    vector<uint> neighbors;

    uint target_vrtx = csa->get_map(vrtx, ContactElementType::TargetVertex);
    
    if (target_vrtx == 0) { // TO DO, check when this will happen? Should happen when we pass a value out of the range. 
        return neighbors; // vrtx does not appears as a source vertex
    }

    uint starting_time = csa->get_map(time, ContactElementType::StartingTime);
    uint ending_time = csa->get_map(time, ContactElementType::EndingTime);

    uint lv, rv; // range A[lu, ru] for vertex u
    uint lts, rts; // range A[lts, rts] for starting time ts
    uint lte, rte; // range A[lte, rte] for ending time te

    tie(lv, rv) = csa->CSA_binary_search(target_vrtx);
    tie(lts, rts) = csa->CSA_binary_search(starting_time);
    tie(lte, rte) = csa->CSA_binary_search(ending_time);

    for (uint i = lv; i <= rv; i++) {
        uint y = csa->psi[i]; // x = position of target vertex
        if (y - 1 <= rts) {
            uint z = csa->psi[y - 1]; // z = position of ending time
            if (z - 1 > rte) {
                uint u = csa->psi[z - 1];
                neighbors.push_back(csa->get_unmap(csa->S[csa->D->rank1(u - 1) - 1], ContactElementType::SrcVertex));
            }
        }
    }

    return neighbors;
}

/**
 * Get all active edges in a given time
 * 
 * @param uint time
 * @return `vector<pair<uint, uint>>` A list o active edges (pairs of vertex)
 */
vector<pair<uint, uint>> TGCSA::snapshot(uint time) {
    vector<pair<uint, uint>> snaps;
    
    uint starting_time = csa->get_map(time, ContactElementType::StartingTime);
    uint ending_time = csa->get_map(time, ContactElementType::EndingTime);

    uint lts, rts; // range A[lts, rts] for starting time ts
    uint lte, rte; // range A[lte, rte] for ending time te

    tie(lts, rts) = csa->CSA_binary_search(starting_time);
    tie(lte, rte) = csa->CSA_binary_search(ending_time);

    uint n = csa->sid.size() / 4;
    for (uint i = 2 * n;  i <= rts; i++) {
        uint z = csa->psi[i];
        if (z - 1 > rte) {
            uint x = csa->psi[z - 1];
            uint y = csa->psi[x - 1];

            uint u = csa->get_unmap(csa->S[csa->D->rank1(x - 1) - 1], ContactElementType::SrcVertex);
            uint v = csa->get_unmap(csa->S[csa->D->rank1(y - 1) - 1], ContactElementType::TargetVertex);

            snaps.push_back(make_pair(u, v));
        }
    }

    return snaps;
}