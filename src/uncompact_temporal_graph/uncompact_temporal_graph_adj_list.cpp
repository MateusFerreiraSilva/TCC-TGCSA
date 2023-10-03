#include "uncompact_temporal_graph_adj_list.h"

pair<uint, uint> get_max_vrtx_and_time(vector<Contact> contacts) {
    uint max_vrtx, max_time; 
    for (auto c : contacts) {
        max_vrtx = max(max(max_vrtx, c.u), max(max_vrtx, c.v));
        max_time = max(max(max_time, c.ts), max(max_time, c.te));
    }

    return make_pair(max_vrtx, max_time);
}

UncompactTemporalGraphAdjList::UncompactTemporalGraphAdjList(vector<Contact> contacts) {
    uint max_vrtx, max_time;
    tie(max_vrtx, max_time) = get_max_vrtx_and_time(contacts);

    temporal_adj_list.resize(max_time);
    for (uint i = 0; i < temporal_adj_list.size(); i++) {
        temporal_adj_list[i].resize(max_vrtx);
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
}

vector<uint> UncompactTemporalGraphAdjList::reverse_neighbors(uint vrtx, uint time) {
    return direct_neighbors(vrtx, time);
}