
#include <chrono>
#include <condition_variable>
#include <mutex>

#include <pthread.h>
#include <time.h>

#include <benchmark/benchmark.h>

// condition variable wait for 0 seconds
static void bm_std_cv_wait_for_0nanaoseconds(benchmark::State& state) {
  std::condition_variable cv;
  std::mutex mtx;
  std::unique_lock lock(mtx, std::defer_lock);

  while (state.KeepRunning()) {
    lock.lock();
    cv.wait_for(lock, std::chrono::nanoseconds(0));
    lock.unlock();
  }
}
BENCHMARK(bm_std_cv_wait_for_0nanaoseconds);

static void bm_pthread_cv_wait_for_0nanaoseconds(benchmark::State& state) {
  pthread_cond_t cv = PTHREAD_COND_INITIALIZER;
  pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
  timespec abstime{};

  while (state.KeepRunning()) {
    abstime.tv_sec = time(NULL);
    pthread_mutex_lock(&mtx);
    pthread_cond_timedwait(&cv, &mtx, &abstime);
    pthread_mutex_unlock(&mtx);
  }
}
BENCHMARK(bm_pthread_cv_wait_for_0nanaoseconds);

// mutex lock/unlock
static void bm_std_mutex_lock_unlock(benchmark::State& state) {
  std::mutex mtx;

  while (state.KeepRunning()) {
    mtx.lock();
    mtx.unlock();
  }
}
BENCHMARK(bm_std_mutex_lock_unlock);

static void bm_pthread_mutex_lock_unlock(benchmark::State& state) {
  pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;

  while (state.KeepRunning()) {
    pthread_mutex_lock(&mtx);
    pthread_mutex_unlock(&mtx);
  }
}
BENCHMARK(bm_pthread_mutex_lock_unlock);

BENCHMARK_MAIN();
