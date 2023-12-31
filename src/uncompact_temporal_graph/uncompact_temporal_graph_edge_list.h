#include <sys/types.h>
#include <vector>
#include <tuple>

#include "uncompact_temporal_graph_utils.h"

using namespace std;

class UncompactTemporalGraphEdgeList {
    public:
        vector<vector<pair<uint, uint>>> temporal_edge_list;

        UncompactTemporalGraphEdgeList(vector<Contact>* contacts);
        vector<uint> direct_neighbors(uint vrtx, uint time);
        vector<uint> reverse_neighbors(uint vrtx, uint time);
};