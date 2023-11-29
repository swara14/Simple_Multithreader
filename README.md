<h1>SIMPLE MULTITHREADER: <h3>An Updated SimpleLoader in C</h3></h1>

<h2>Overview: </h2>
The provided program facilitates the parallelization of computations through multi-threading. It includes functions for 1D (vector) and 2D (matrix) parallel loops, utilizing Pthreads. The code measures and outputs execution times, enhancing performance by applying user-defined lambda functions to indices or pairs in specified ranges concurrently.

<h2>Implementation: </h2>
  1. get_time():
Returns the current time in milliseconds using the gettimeofday() function. It converts the seconds and microseconds obtained from the system time into milliseconds and returns the result.

  2. thread_args_1D and thread_args_2D:
Structures defining the arguments for 1D and 2D thread functions, including the range (low and high indices) and lambda functions to be applied in parallel.

  3. *thread_func_1D(void ptr) and *thread_func_2D(void ptr):
Takes a pointer to a thread_args_1D structure, iterates over the specified range, and applies the provided lambda function to each index in parallel.
Takes a pointer to a thread_args_2D structure, iterates over the specified 2D range, and applies the provided lambda function to each (i, j) pair in parallel.

  4. parallel_for():
Executes a 1D and 2D parallel loop by dividing the range [low, high) into NTHREADS chunks. It creates and joins threads, each working on a separate chunk, applying the provided lambda function to each index in parallel in 1D and each (i, j) pair in parallel in 2D.
