#include "uncompact_temporal_graph_adj_list.h"

UncompactTemporalGraphAdjList::UncompactTemporalGraphAdjList(vector<Contact> contacts) {
    uint max_vrtx, max_time;
    tie(max_vrtx, max_time) = get_max_vrtx_and_time(contacts);

    temporal_adj_list.resize(max_time + 1);
    for (uint i = 0; i < temporal_adj_list.size(); i++) {
        temporal_adj_list[i].resize(max_vrtx + 1);
    }
    
    for (auto c : contacts) {
        for (uint i = c.ts; i < c.te; i++) {
            temporal_adj_list[i][c.u].push_back(c.v);
        }
    }
}

vector<uint> UncompactTemporalGraphAdjList::direct_neighbors(uint vrtx, uint time) {
    vector<uint> neighbors;
    for (uint i = 0; i < temporal_adj_list[time][vrtx].size(); i++) {
        neighbors.push_back(temporal_adj_list[time][vrtx][i]);
    }
    
    return neighbors;
}

vector<uint> UncompactTemporalGraphAdjList::reverse_neighbors(uint vrtx, uint time) {
    vector<uint> neighbors;
    for (uint i = 0; i < temporal_adj_list[time].size(); i++) {
        for (uint j = 0; j < temporal_adj_list[time][i].size(); j++) {
            if (temporal_adj_list[time][i][j] == vrtx) {
                neighbors.push_back(i);
            }
        }
    }
    
    return neighbors;
}