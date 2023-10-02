#include "data_generator.h"
#include "../utils/file_utils.h"

int main() {
    vector<int> contacts = generate_random_contacts(1000, 100, 500);
    string file_name = "random_contacts.csv";

    write_csv_file(contacts, file_name);
    read_csv_file(file_name);

    return 0;
}