#include <bits/stdc++.h>

using namespace std;

const string default_graph_type = "tgcsa";

class CommandLineInterface {
    private:
        static void print_article_example();
        static vector<string> get_args(int argc, char* argv[]);
        static bool is_debug_mode(vector<string> args);
        static string get_contacts_csv_file_name(vector<string> args);
        static string get_queries_file_name(vector<string> args);
        static string get_temporal_graph_type(vector<string> args);

    public:
        vector<string> args;
        bool debug_mode;
        string contacts_csv_file_name;
        string queries_file_name;
        string temporal_graph_type = default_graph_type;

        CommandLineInterface(int argc, char* argv[]);
};