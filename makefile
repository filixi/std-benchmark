CC = g++

FLAG = -std=c++17

INCLUDE = -I ~/work/benchmark/include # include path of google's benchmark tool
LIB_PATH = -L ~/work/benchmark/build/src # lib path of benchmark tool

LIB = -lbenchmark -lpthread

main:
	$(CC) $(FLAG) main.cc $(INCLUDE) $(LIB_PATH) $(LIB)

run:
	./a.out --benchmark_out=result --benchmark_out_format=console
