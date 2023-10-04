#include "data_generator.h"

/**
 * Get a random integer between 1 and max_value
 * 
 * @param int max_value, the max value that can be generated
 * @return int random number [1, max_value]
 */
int get_random_int(int max_value) {
    return rand() % max_value + 1;
}

/**
 * Generate a random contacts
 * 
 * @param int vrtx_max, the max number that can be generated to vrtx
 * @param int time_max, the max number that can be generated to timestamp
 * @param int edges_number, the total number of edges (connections)
 * @return `vector<int>` A list of random unordered contacts
 */
vector<int> generate_random_contacts(int vrtx_max, int time_max, int edges_number) {
    srand(time(NULL)); // initialize random seed

    const int number_of_conctacts = edges_number * CONTACT_LENGHT;

    vector<int> contacts(number_of_conctacts);
    for (int i = 0; i + 3 < contacts.size(); i += 4) {
        contacts[i] = get_random_int(vrtx_max);
        contacts[i + 1] = get_random_int(vrtx_max);
        contacts[i + 2] = get_random_int(time_max);
        contacts[i + 3] = get_random_int(time_max);

        while (contacts[i] == contacts[i + 1]) { // u and v cant be the same
            contacts[i + 1] = get_random_int(vrtx_max); 
        }

        if (contacts[i + 2] > contacts[i + 3]) { // end time must be greather than initial time
            swap(contacts[i + 2], contacts[i + 3]);
        }
    }

    return contacts;
}