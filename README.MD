Run on (8 X 3500 MHz CPU s)
2017-09-19 12:10:14
----------------------------------------------------------------------------
Benchmark                                     Time           CPU Iterations
----------------------------------------------------------------------------
bm_std_cv_wait_for_0nanaoseconds          51766 ns       1432 ns     100000
bm_pthread_cv_wait_for_0nanaoseconds       2593 ns       1384 ns     497915
bm_std_mutex_lock_unlock                     16 ns         16 ns   41765564
bm_pthread_mutex_lock_unlock                 18 ns         18 ns   40071018
