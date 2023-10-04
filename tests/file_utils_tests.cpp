#include <gtest/gtest.h>
#include "../src/utils/file_utils.h"
#include "../src/data_generator/data_generator.h"

TEST(FileUtilsTests, WriteAndReadTest) {
    vector<int> contacts = generate_random_contacts(1000, 100, 500);
    string file_name = "test_contacts.csv";

    write_csv_file(contacts, file_name);
    vector<int> contacts_from_file = read_csv_file_int(file_name);

    ASSERT_EQ(contacts, contacts_from_file);
}