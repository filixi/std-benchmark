
#include <chrono>
#include <condition_variable>
#include <mutex>
#include <thread>

#include <pthread.h>
#include <time.h>

#include <benchmark/benchmark.h>

// condition variable wait for 1 nanosecond
static void bm_std_cv_wait_for_1nanosecond(benchmark::State& state) {
  std::condition_variable cv;
  std::mutex mtx;
  std::unique_lock lock(mtx, std::defer_lock);

  while (state.KeepRunning()) {
    lock.lock();
    cv.wait_for(lock, std::chrono::nanoseconds(0));
    lock.unlock();
  }
}
BENCHMARK(bm_std_cv_wait_for_1nanosecond);

static void bm_pthread_cv_wait_for_1nanosecond(benchmark::State& state) {
  pthread_cond_t cv = PTHREAD_COND_INITIALIZER;
  pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
  timespec abstime = {.tv_sec = 0, .tv_nsec = 1};

  while (state.KeepRunning()) {
    abstime.tv_sec = time(NULL);
    pthread_mutex_lock(&mtx);
    pthread_cond_timedwait(&cv, &mtx, &abstime);
    pthread_mutex_unlock(&mtx);
  }
}
BENCHMARK(bm_pthread_cv_wait_for_1nanosecond);

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

// sleep for 1 nano second
static void bm_std_sleep_for_1nanosecond(benchmark::State& state) {
  while (state.KeepRunning()) {
    std::this_thread::sleep_for(std::chrono::nanoseconds(1));
  }
}
BENCHMARK(bm_std_sleep_for_1nanosecond);

static void bm_pthread_sleep_for_1nanosecond(benchmark::State& state) {
  timespec reltime{0, 1};

  while (state.KeepRunning()) {
    nanosleep(&reltime, nullptr);
  }
}
BENCHMARK(bm_pthread_sleep_for_1nanosecond);

BENCHMARK_MAIN();
