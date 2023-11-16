#include <iostream>
#include <list>
#include <functional>
#include <stdlib.h>
#include <cstring>
#include <functional>
#include <pthread.h>
#include <chrono>
#include <time.h>
#include <sys/time.h>

int user_main(int argc, char **argv);

long get_time(){
    struct timeval time, *address_time = &time;
    if (gettimeofday(address_time, NULL) != 0) {
        perror("Error in printing the time.");
        exit(1);
    }
    long epoch_time = time.tv_sec * 1000;
    return epoch_time + time.tv_usec / 1000;
}

typedef struct {
    int low, high;
    std::function<void (int)> lambda1D;
} thread_args_1D;

typedef struct {
    int low1,low2, high1, high2;
    std::function<void (int, int)> lambda2D;
} thread_args_2D;

void *thread_func_1D(void *ptr) {
    thread_args_1D * t = ((thread_args_1D *) ptr);
    for (int i = t->low; i < t->high; i++)
    {
        t->lambda1D(i);
    }
    return NULL;
}

void *thread_func_2D(void *ptr) {
    thread_args_2D * t = ((thread_args_2D *) ptr);

    for (int i = t->low1; i < t->high1; i++)
    {
        for (int j = t->low2; j < t->high2; j++){
            t->lambda2D(i, j);
        }    
    }
    return NULL;
}

void parallel_for(int low, int high, std::function<void(int)> &&lambda, int NTHREADS) {
    
    long start_time=get_time();
    pthread_t tid[NTHREADS];
    thread_args_1D args[NTHREADS];
    int chunk = (high - low )/NTHREADS;

    for (int i=0; i<NTHREADS; i++) {
        args[i].low=i*chunk; 
        args[i].high = (i+1)*chunk;       
        if (i == NTHREADS - 1) {
            args[i].high = high; 
        }    
        args[i].lambda1D = lambda;
        pthread_create(&tid[i],NULL,thread_func_1D,(void*) &args[i]);
    }
    for (int i=0; i<NTHREADS; i++) {
        pthread_join(tid[i] , NULL);
    }
    long end_time=get_time();

    printf("Start time for vector: %ld\n", start_time);
    printf("End time for vector: %ld\n", end_time);
    long t1 = end_time-start_time;
    printf("Total execution time for vector: %ld\n", t1);
}

void parallel_for(int low1, int high1, int low2, int high2, std::function<void(int, int)> &&lambda, int NTHREADS){
    long start_time=get_time();
    pthread_t tid[NTHREADS];
    thread_args_2D args[NTHREADS];
    int chunk1 = (high1 - low1 )/NTHREADS;
    //int chunk2 = (high2 - low2) / NTHREADS;

    for (int i=0; i<NTHREADS; i++) {

        args[i].low1 =i*chunk1; 
        args[i].high1 = (i+1)*chunk1;
        args[i].low2 = 0; 
        args[i].high2 = high1;  
        if (i == NTHREADS - 1) {
            args[i].high1 = high1; 
        }
        args[i].lambda2D = lambda;
        pthread_create(&tid[i],NULL,thread_func_2D,(void*) &args[i]);

    }

    for (int i=0; i<NTHREADS; i++) {
        pthread_join(tid[i] , NULL);
    }
    long end_time=get_time();
    long t2=end_time-start_time;
    printf("Start time for matrix: %ld\n", start_time);
    printf("End time for matix: %ld\n", end_time);
    printf("Total execution time for matrix: %ld\n", t2);
}
int main(int argc, char **argv) {
  int rc = user_main(argc, argv);
  return rc;
}

#define main user_main
