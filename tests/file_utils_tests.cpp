#include <gtest/gtest.h>
#include "../benchmark/data_generator/file_utils.h"
#include "../benchmark/data_generator/data_generator.h"

TEST(FileUtilsTests, WriteAndReadTest) {
    vector<int> contacts = generate_random_contacts(1000, 100, 500);
    string file_name = "test_contacts.csv";

    write_csv_file(contacts, file_name);
    vector<int> contacts_from_file = read_csv_file(file_name);

    ASSERT_EQ(contacts, contacts_from_file);
}