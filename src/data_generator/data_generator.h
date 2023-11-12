#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <sstream>

using namespace std;

#define CONTACT_LENGHT 4

vector<int> generate_random_contacts(int vrtx_max, int time_max, int edges_number);
vector<string> generate_random_queries(const vector<int> used_vrtx, int time_max, int queries_number);