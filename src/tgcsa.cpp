#include "tgcsa.h"

TGCSA::TGCSA(vector<Contact> & contacts) {
    csa = new CompactSuffixArray(contacts);
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
        uint x = csa->Psi[i]; // x = position of target vertex
        uint y = csa->Psi[x - 1]; // y = position of starting time
        if (y - 1 <= rts) {
            uint z = csa->Psi[y - 1]; // z = position of ending time
            if (z - 1 > rte) {
                // neighbors.push_back(get_unmap(x, ContactElementType::TargetVertex));
                neighbors.push_back(csa->get_unmap(csa->sid[csa->A[x - 1] - 1], ContactElementType::TargetVertex));
            }
        }
    }

    return neighbors;
}

/**
 * Gets the direct neighbors of a given vrtx in a given time, where t1 < time < t2
 * 
 * @param uint src vrtx
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
        uint y = csa->Psi[i]; // x = position of target vertex
        if (y - 1 <= rts) {
            uint z = csa->Psi[y - 1]; // z = position of ending time
            if (z - 1 > rte) {
                uint u = csa->Psi[z - 1];
                neighbors.push_back(csa->get_unmap(csa->sid[csa->A[u - 1] - 1], ContactElementType::SrcVertex));
            }
        }
    }

    return neighbors;
}