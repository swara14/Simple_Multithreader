#include <iostream>
#include <list>
#include <functional>
#include <stdlib.h>
#include <cstring>
#include <functional>
#include <pthread.h>
#include <chrono>

int user_main(int argc, char **argv);

struct ThreadArgs {
  std::function<void(int)> lambda1D;
  int low, high;
};

void* threadWorker(void *args) {
    ThreadArgs *threadArgs = static_cast<ThreadArgs *>(args);

    if (threadArgs->lambda1D) {
        for (int i = threadArgs->low; i <= threadArgs->high; ++i) {
            threadArgs->lambda1D(i);
        }
    }
    return nullptr;
}

void parallel_for(int low, int high, std::function<void(int)> &&lambda, int numThreads) {
    auto start_time = std::chrono::high_resolution_clock::now();

    pthread_t *threads = new pthread_t[numThreads];

    int range = (high - low + 1) / numThreads;

    for (int i = 0; i < numThreads; ++i) {
        ThreadArgs args;
        args.lambda1D = std::move(lambda);
        args.low = low + i * range;
        args.high = (i == numThreads - 1) ? high : (low + (i + 1) * range - 1);

        pthread_create(&threads[i], nullptr, threadWorker, &args);
    }

    for (int i = 0; i < numThreads; ++i) {
        pthread_join(threads[i], nullptr);
    }

    delete[] threads;

    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
    std::cout << "Execution time: " << duration.count() << " microseconds\n";
}

int main(int argc, char **argv) {
  int rc = user_main(argc, argv);
  return rc;
}

#define main user_main


