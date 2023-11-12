#include <sys/types.h>
#include <vector>
#include <tuple>

#include "uncompact_temporal_graph_utils.h"

using namespace std;

class UncompactTemporalGraphAdjList  {
    public:
        vector<vector<vector<uint>>> temporal_adj_list;

        UncompactTemporalGraphAdjList(vector<Contact>* contacts);
        vector<uint> direct_neighbors(uint vrtx, uint time);
        vector<uint> reverse_neighbors(uint vrtx, uint time);
};