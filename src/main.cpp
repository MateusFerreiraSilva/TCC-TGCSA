#include <bits/stdc++.h>
#include "tgcsa/tgcsa.h"
#include "tgcsa/compact_suffix_array.h"
#include "uncompact_temporal_graph/uncompact_temporal_graph_adj_list.h"
#include "uncompact_temporal_graph/uncompact_temporal_graph_edge_list.h"
#include "utils/file_utils.h"

using namespace std;

void bookExample() {
    vector<Contact> contacts {
        Contact(1, 3, 1, 8),
        Contact(1, 4, 5, 8),
        Contact(2, 1, 1, 5),
        Contact(4, 3, 7, 8),
        Contact(4, 5, 5, 7)
    };

    puts("Contacts:\n");
    for(auto c : contacts) {
        c.print();
        printf(" ");
    }
    puts("");

    CompactSuffixArray csa(contacts);

    csa.print();
}

vector<string> get_args(int argc, char* argv[]) {
    vector<string> args;
    
    for (uint i = 0; i < argc; i++) {
        args.push_back(argv[i]);
    }

    return args;
}

map<string, bool> get_execution_parameters(int argc, char* argv[]) {
    vector<string> args = get_args(argc, argv);

    map<string, bool> execution_parameters = {
        { "debug", (find(args.begin(), args.end(), "--debug") != args.end()) },
        { "file", (find(args.begin(), args.end(), "--file") != args.end()) },
        { "tgcsa", (find(args.begin(), args.end(), "--tgcsa") != args.end()) },
        { "adj_list", (find(args.begin(), args.end(), "--adj_list") != args.end()) },
        { "edge_list", (find(args.begin(), args.end(), "--edge_list") != args.end()) }
    };

    return execution_parameters;
}

string get_file_name(int argc, char* argv[]) {
    vector<string> args = get_args(argc, argv);

    auto it = next(find(args.begin(), args.end(), "--file"), 1);
    string file_name = *it;

    return file_name;
}


int main(int argc, char* argv[]) {
    auto parameters = get_execution_parameters(argc, argv);

    if (parameters["debug"]) {
        bookExample();
    }

    if (parameters["file"]) {
        string file_name = get_file_name(argc, argv);
        vector<Contact> contacts = read_csv_file(file_name);

        cout << contacts.size() << endl;
    
        vector<uint> neighbors;

        if (parameters["tgcsa"]) {
            auto tgcsa = new TGCSA(contacts);
            neighbors = tgcsa->direct_neighbors(4, 5);
        }
        else if (parameters["adj_list"]) {
            auto adj_list = new UncompactTemporalGraphAdjList(contacts);
            neighbors = adj_list->direct_neighbors(4, 5);
        } else if (parameters["edge_list"]) {
            auto edge_list = new UncompactTemporalGraphEdgeList(contacts);
            neighbors = edge_list->direct_neighbors(4, 5);
        }

        cout << "neighbors:" << endl;
        for (auto n : neighbors) {
            cout << n << endl;
        }
    }

    return 0;
}