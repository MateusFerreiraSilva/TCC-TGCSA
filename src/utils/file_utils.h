#include <bits/stdc++.h>
#include "contact.h"
#include "temporal_graph_query.h"
using namespace std;

void write_csv_file(vector<int> contacts, string file_name);
void write_file(vector<string> lines, string file_name);
vector<int> read_csv_file_int(string file_name);
vector<Contact>* read_csv_file(string file_name);
vector<TemporalGraphQuery> read_queries_file(string file_name);