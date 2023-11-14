#include <iostream>
#include <list>
#include <functional>
#include <stdlib.h>
#include <cstring>
#include <functional>
#include <pthread.h>
#include <chrono>

int user_main(int argc, char **argv);

typedef struct {
    int low;
    int high;
    std::function<void (int)> lambda1D;

} thread_args;

void *thread_func(void *ptr) {
    thread_args * t = ((thread_args *) ptr);
    t->lambda1D;
    for (int i = t->low; i <= t->high; i++)
    {
        t->lambda1D(i);
    }
    return NULL;
}

void parallel_for(int low, int high, std::function<void(int)> &&lambda, int NTHREADS) {
    pthread_t tid[NTHREADS];
    thread_args args[NTHREADS];
    int chunk = (high - low )/NTHREADS;
    for (int i=0; i<NTHREADS; i++) {
        args[i].low=i*chunk; 
        args[i].high = (i+1)*chunk;        
        args[i].lambda1D = lambda;
        pthread_create(&tid[i],NULL,thread_func,(void*) &args[i]);
    }
    for (int i=0; i<NTHREADS; i++) {
        pthread_join(tid[i] , NULL);
    }
}

int main(int argc, char **argv) {
  int rc = user_main(argc, argv);
  return rc;
}

#define main user_main


