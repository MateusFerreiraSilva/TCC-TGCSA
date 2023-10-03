#include <bits/stdc++.h>
#include "../utils/contact.h"
using namespace std;

class UncompactTemporalGraphEdgeList {
    public:
        vector<vector<pair<uint, uint>>> temporal_edge_list;

        UncompactTemporalGraphEdgeList(vector<Contact> contacts);
        vector<uint> direct_neighbors(uint vrtx, uint time);
        vector<uint> reverse_neighbors(uint vrtx, uint time);
};