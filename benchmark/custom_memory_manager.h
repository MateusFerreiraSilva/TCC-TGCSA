// credits to https://github.com/google/benchmark/issues/1217#issuecomment-1146149457

#include <benchmark/benchmark.h>
#include <memory>

using namespace std;

class CustomMemoryManager: public benchmark::MemoryManager {
    public:
        int64_t num_allocs;
        int64_t max_bytes_used;

        void Start() BENCHMARK_OVERRIDE {
            num_allocs = 0;
            max_bytes_used = 0;
        }

        void Stop(Result& result) BENCHMARK_OVERRIDE {
            result.num_allocs = num_allocs;
            result.max_bytes_used = max_bytes_used;
        }
};

unique_ptr<CustomMemoryManager> memory_manager(new CustomMemoryManager());

#ifdef MEMORY_PROFILER // TO DO remove this
void *custom_malloc(size_t size) {
    void *p = malloc(size);
    memory_manager.get()->num_allocs += 1;
    memory_manager.get()->max_bytes_used += size;
    return p;
}
#define malloc(size) custom_malloc(size)
#endif