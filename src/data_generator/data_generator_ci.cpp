#include "data_generator.h"
#include "../utils/file_utils.h"

int main() {
    int vrtx_max = 100000;
    int time_max = 300;
    int edges_number = 1000;
    int queries_number = 100;

    string file_name = "random_contacts.csv";
    string random_queries_file = "queries.txt";

    cout << "creating random_contacts.csv..." << endl;
    vector<int> contacts = generate_random_contacts(vrtx_max, time_max, edges_number);
    write_csv_file(contacts, file_name);
    cout << "random_contacts.csv created!" << endl;

    cout << "creating queries.txt" << endl;
    vector<string> queries = generate_random_queries(vrtx_max, time_max, queries_number);
    write_file(queries, random_queries_file);
    cout << "queries.txt created!" << endl;

    return 0;
}