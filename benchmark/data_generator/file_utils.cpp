#include "file_utils.h"

void write_csv_file(vector<int> contacts, string file_name) {
    ofstream file(file_name.c_str());

    file << "u,";
    file << "v,";
    file << "ts,";
    file << "te";
    file << endl;

    for (int i = 0; i + 3 < contacts.size(); i  += 4) {
        file << contacts[i] << ",";
        file << contacts[i + 1] << ",";
        file << contacts[i + 2] << ",";
        file << contacts[i + 3] << endl;
    }

    file.close();
}