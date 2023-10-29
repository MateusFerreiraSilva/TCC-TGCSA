#include <gtest/gtest.h>

#include "../src/tgcsa/tgcsa.h"
#include "../src/uncompact_temporal_graph/uncompact_temporal_graph_adj_list.h"
#include "../src/uncompact_temporal_graph/uncompact_temporal_graph_edge_list.h"
#include "../src/utils/file_utils.h"

/* file with 500 contacts, where the vrtx can be between [1, 10] and the max time is 100*/
const string test_data_file_name = "../../tests/test_data/random_contacts_test_01.csv";
const int test_data_contacts_number = 500;

vector<pair<int, int>> queries {
    make_pair(4, 5),
    make_pair(1, 20),
    make_pair(10, 60),
    make_pair(8, 80),
    make_pair(3, 13),
    make_pair(9, 1),
    make_pair(9, 100),
};

vector<Contact>* contacts = read_csv_file(test_data_file_name);
vector<Contact>* tgcsa_contacts = read_csv_file(test_data_file_name);
vector<Contact>* adj_list_contacts = read_csv_file(test_data_file_name);
vector<Contact>* edge_list_contacts = read_csv_file(test_data_file_name);

const auto tgcsa = new TGCSA(tgcsa_contacts);
const auto adj_list = new UncompactTemporalGraphAdjList(adj_list_contacts);
const auto edge_list = new UncompactTemporalGraphEdgeList(edge_list_contacts);

TEST(GraphsTests, GraphsDirectNeighborsTest) {
    ASSERT_EQ(contacts->size(), test_data_contacts_number);

    for (const auto& q : queries) {
        auto tgcsa_direct_neighbors = tgcsa->direct_neighbors(q.first, q.second);
        auto adj_list_direct_neighbors = adj_list->direct_neighbors(q.first, q.second);
        auto edge_list_direct_neighbors = edge_list->direct_neighbors(q.first, q.second);

        // the order of the response depends on the structure
        sort(tgcsa_direct_neighbors.begin(), tgcsa_direct_neighbors.end());
        sort(adj_list_direct_neighbors.begin(), adj_list_direct_neighbors.end());
        sort(edge_list_direct_neighbors.begin(), edge_list_direct_neighbors.end());

        ASSERT_EQ(tgcsa_direct_neighbors, adj_list_direct_neighbors);
        ASSERT_EQ(tgcsa_direct_neighbors, edge_list_direct_neighbors);
    }
}

TEST(GraphsTests, GraphsReverseNeighborsTest) {
    ASSERT_EQ(contacts->size(), test_data_contacts_number);

    for (const auto& q : queries) {
        auto tgcsa_reverse_neighbors = tgcsa->reverse_neighbors(q.first, q.second);
        auto adj_list_reverse_neighbors = adj_list->reverse_neighbors(q.first, q.second);
        auto edge_list_reverse_neighbors = edge_list->reverse_neighbors(q.first, q.second);

        // the order of the response depends on the structure
        sort(tgcsa_reverse_neighbors.begin(), tgcsa_reverse_neighbors.end());
        sort(adj_list_reverse_neighbors.begin(), adj_list_reverse_neighbors.end());
        sort(edge_list_reverse_neighbors.begin(), edge_list_reverse_neighbors.end());

        ASSERT_EQ(tgcsa_reverse_neighbors, adj_list_reverse_neighbors);
        ASSERT_EQ(tgcsa_reverse_neighbors, edge_list_reverse_neighbors);
    }
}