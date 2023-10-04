#include "uncompact_temporal_graph_edge_list.h"

UncompactTemporalGraphEdgeList::UncompactTemporalGraphEdgeList(vector<Contact> contacts) {
    uint max_vrtx, max_time;
    tie(max_vrtx, max_time) = get_max_vrtx_and_time(contacts);

    temporal_edge_list.resize(max_time + 1);
    
    for (auto c : contacts) {
        for (uint i = c.ts; i < c.te; i++) {
            temporal_edge_list[i].push_back(make_pair(c.u, c.v));
        }
    }
}

vector<uint> UncompactTemporalGraphEdgeList::direct_neighbors(uint vrtx, uint time) {
    vector<uint> neighbors;
    for (auto edge : temporal_edge_list[time]) {
        if (edge.first == vrtx) {
            neighbors.push_back(edge.second);
        }
    }

    return neighbors;
}

vector<uint> UncompactTemporalGraphEdgeList::reverse_neighbors(uint vrtx, uint time) {
    vector<uint> neighbors;
    for (auto edge : temporal_edge_list[time]) {
        if (edge.second == vrtx) {
            neighbors.push_back(edge.first);
        }
    }

    return neighbors;
}