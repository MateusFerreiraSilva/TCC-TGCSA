#include "data_generator.h"
#include "../utils/file_utils.h"

int main() {
    string file_name = "random_contacts.csv";
    string random_queries_file = "queries.txt";

    int edges_number, queries_number, vrtx_max, time_max;

    cout << "Total number of edges: ";
    cin >> edges_number;

    cout << "Total number of queries: ";
    cin >> queries_number;

    cout << "Vertex maximum value: ";
    cin >> vrtx_max;

    cout << "Time maximum value: ";
    cin >> time_max;

    cout << endl << "creating random_contacts.csv..." << endl;
    vector<int> contacts = generate_random_contacts(vrtx_max, time_max, edges_number);
    write_csv_file(contacts, file_name);
    cout << "random_contacts.csv created!" << endl;

    set<int> used_vrtx;
    for (int i = 0; i + CONTACT_LENGHT < contacts.size(); i += 2) {
        const int src_vrtx = contacts[i];
        const int target_vrtx = contacts[i + 1];

        used_vrtx.insert(src_vrtx);
        used_vrtx.insert(target_vrtx);
    }

    cout << endl << "creating queries.txt" << endl;
    vector<string> queries = generate_random_queries(vector<int>(used_vrtx.begin(), used_vrtx.end()), time_max, queries_number);
    write_file(queries, random_queries_file);
    cout << "queries.txt created!" << endl;

    return 0;
}