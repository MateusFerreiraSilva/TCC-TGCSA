#include "file_utils.h"

void write_csv_file(vector<int> contacts, string file_name) {
    ofstream file;
    
    file.open(file_name.c_str(), ofstream::out);

    file << "u,";
    file << "v,";
    file << "ts,";
    file << "te";
    file << endl;

    for (int i = 0; i + 3 < contacts.size(); i += 4) {
        file << contacts[i] << ",";
        file << contacts[i + 1] << ",";
        file << contacts[i + 2] << ",";
        file << contacts[i + 3] << endl;
    }

    file << flush;

    file.close();
}

void write_file(vector<string> lines, string file_name) {
    ofstream file;

    file.open(file_name.c_str(), ofstream::out);

    for (const auto& l : lines) {
        file << l << endl;
    }

    file << flush;

    file.close();
}

vector<string> string_split(string str, char delimiter) {
    vector<string> slices;

    int range_start = 0;
    for (int i = 0; i < str.size(); i++) {
        if (str[i] == delimiter) {
            string s;
            for (int j = range_start; j < i; j++) {
                s.push_back(str[j]);
            }
            slices.push_back(s);

            range_start = i + 1;
        }
    }

    string last_value;
    for (int i = range_start; i < str.size(); i++) {
        last_value.push_back(str[i]);
    }
    slices.push_back(last_value);

    return slices;
}

vector<int> read_csv_file_int(string file_name) {
    vector<int> contacts;

    ifstream file;
    file.open(file_name.c_str(), ifstream::in);

    string csv_header, csv_line;
    
    file >> csv_header;
    while (file >> csv_line) {
        vector<string> contact_values = string_split(csv_line, ',');

        for (const auto& c : contact_values) {
            uint value = stoi(c, nullptr, 0);
            contacts.push_back(value);
        }
    }

    return contacts;
}

vector<Contact>* read_csv_file(string file_name) {
    vector<Contact>* contacts = new vector<Contact>();
    vector<int> contacts_int = read_csv_file_int(file_name);

    for (uint i = 0; i + 3 < contacts_int.size(); i += 4) {
        Contact c(
            (uint)contacts_int[i], (uint)contacts_int[i + 1],
            (uint)contacts_int[i + 2], (uint)contacts_int[i + 3]
        );

        contacts->push_back(c);
    }

    return contacts;
}

vector<TemporalGraphQuery> read_queries_file(string file_name) {
    vector<TemporalGraphQuery> queries;
    
    ifstream file;
    file.open(file_name.c_str(), ifstream::in);

    string query;
    while (file >> query) {
        vector<string> query_params = string_split(query, ',');

        if (query_params.size() == 3) {
            queries.push_back(
                TemporalGraphQuery(
                    query_params[0],
                    (uint) stoi(query_params[1], nullptr, 0),
                    (uint) stoi(query_params[2], nullptr, 0)
                )
            );
        }
    }

    return queries;
}