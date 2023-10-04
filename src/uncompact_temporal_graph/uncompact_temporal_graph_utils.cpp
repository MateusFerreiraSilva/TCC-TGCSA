#include "uncompact_temporal_graph_utils.h"

pair<uint, uint> get_max_vrtx_and_time(vector<Contact> contacts) {
    uint max_vrtx, max_time; 
    for (auto c : contacts) {
        max_vrtx = max(max(max_vrtx, c.u), max(max_vrtx, c.v));
        max_time = max(max(max_time, c.ts), max(max_time, c.te));
    }

    return make_pair(max_vrtx, max_time);
}
