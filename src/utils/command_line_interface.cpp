#include "command_line_interface.h"

void CommandLineInterface::print_article_example() {
    vector<Contact> contacts {
        Contact(1, 3, 1, 8),
        Contact(1, 4, 5, 8),
        Contact(2, 1, 1, 5),
        Contact(4, 3, 7, 8),
        Contact(4, 5, 5, 7)
    };

    TGCSA tgcsa(contacts, true);
}

vector<string> CommandLineInterface::get_args(int argc, char* argv[]) {
    vector<string> args;
    
    for (uint i = 0; i < argc; i++) {
        args.push_back(argv[i]);
    }

    return args;
}

bool CommandLineInterface::is_debug_mode(vector<string> args) {
    const string debug_arg = "--debug";
    return find(args.begin(), args.end(), debug_arg) != args.end();
}

string CommandLineInterface::get_contacts_csv_file_name(vector<string> args) {
    const string file_arg = "--file";
    const string delimitor = "=";
    const string csv_ext = ".csv";

    for (auto a : args) {
        int patter_idx = a.find(file_arg);
        if (patter_idx != string::npos) {
            int delimitor_idx = a.find(delimitor);
            string file_name = a.substr(delimitor_idx + 1);
            if (file_name.find(csv_ext) != string::npos) {
                return file_name;
            }
            break;
        }
    }

    return "";
}

string CommandLineInterface::get_queries_file_name(vector<string> args) {
    const string queries_arg = "--queries";
    const string delimitor = "=";

    for (auto a : args) {
        int patter_idx = a.find(queries_arg);
        if (patter_idx != string::npos) {
            int delimitor_idx = a.find(delimitor);
            string queries_file_name = a.substr(delimitor_idx + 1);

            return queries_file_name;
        }
    }

    return "";
}

string CommandLineInterface::get_temporal_graph_type(vector<string> args) {
    const string temporal_graph_arg = "--temporal_graph";
    const string delimitor = "=";
    const vector<string> temporal_graphs_valid_types {
        "tgcsa", "adj_list", "edge_list"
    };

    for (auto a : args) {
        int patter_idx = a.find(temporal_graph_arg);
        if (patter_idx != string::npos) {
            int delimitor_idx = a.find(delimitor);
            string temporal_graph_type = a.substr(delimitor_idx + 1);
            if (find(temporal_graphs_valid_types.begin(), temporal_graphs_valid_types.end(), temporal_graph_type) !=
                temporal_graphs_valid_types.end()) {
                return temporal_graph_type;

            }

            break;
        }
    }

    return "";
}

vector<Contact> CommandLineInterface::get_contacts() {
    vector<Contact> contacts;
    if (!contacts_csv_file_name.empty()) {
        contacts = read_csv_file(contacts_csv_file_name); 
    }

    return contacts;
}

CommandLineInterface::CommandLineInterface(int argc, char* argv[]) {
    args = get_args(argc, argv);

    if (args.size() == 1) {
        print_article_example();
        return;
    }

    debug_mode = is_debug_mode(args);
    contacts_csv_file_name = get_contacts_csv_file_name(args);
    queries_file_name = get_queries_file_name(args);
    temporal_graph_type = get_temporal_graph_type(args);

    run_queries();
}

void CommandLineInterface::run_queries() {
    vector<TemporalGraphQuery> queries = read_queries_file(queries_file_name);
    vector<Contact> contacts = get_contacts();

    if (temporal_graph_type == "adj_list") {
        UncompactTemporalGraphAdjList temporal_graph(contacts);

        for (auto query : queries) {
            if (query.queryType == TemporalGraphQueryType::DirectNeighbors) {
                temporal_graph.direct_neighbors(query.vrtx, query.time);
            } else {
                temporal_graph.reverse_neighbors(query.vrtx, query.time);
            }
        }
    } else if (temporal_graph_type == "edge_list") {
        UncompactTemporalGraphEdgeList temporal_graph(contacts);

        for (auto query : queries) {
            if (query.queryType == TemporalGraphQueryType::DirectNeighbors) {
                temporal_graph.direct_neighbors(query.vrtx, query.time);
            } else {
                temporal_graph.reverse_neighbors(query.vrtx, query.time);
            }
        }
    } else {
        TGCSA temporal_graph(contacts);

        for (auto query : queries) {
            if (query.queryType == TemporalGraphQueryType::DirectNeighbors) {
                temporal_graph.direct_neighbors(query.vrtx, query.time);
            } else {
                temporal_graph.reverse_neighbors(query.vrtx, query.time);
            }
        }
    }
}