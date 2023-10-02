#include <benchmark/benchmark.h>
#include "../../src/tgcsa/tgcsa.h"

static void direct_neighbors_benchmark() {
    uint src_vrtx = 1;
    uint time = 5;

    vector<Contact> contacts {
        Contact(1, 3, 1, 8),
        Contact(1, 4, 5, 8),
        Contact(2, 1, 1, 5),
        Contact(4, 3, 7, 8),
        Contact(4, 5, 5, 7)
    };



    TGCSA tgcsa(contacts);

    auto neighbors = tgcsa.direct_neighbors(1, 5);

    // cout << "neighbors:";
    // for (auto n : neighbors) {
    //   cout << " " << n;
    // }
    // cout << endl;
}

static void TGCSA_BENCHMARK(benchmark::State& state) {
  for (auto _ : state) {
    direct_neighbors_benchmark();
  }
}
// Register the function as a benchmark
BENCHMARK(TGCSA_BENCHMARK);

BENCHMARK_MAIN();