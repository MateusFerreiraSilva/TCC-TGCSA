#include <bits/stdc++.h>
#include "../utils/contact.h"
using namespace std;

class UncompactTemporalGraph {
    public:
        vector<vector<vector<uint>>> temporal_adj_list;

        UncompactTemporalGraph(vector<Contact> contacts);

        vector<uint> direct_neighbors(uint vrtx, uint time);
};