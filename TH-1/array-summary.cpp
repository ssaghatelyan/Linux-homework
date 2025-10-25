#include <iostream>
#include <pthread.h>
#include <chrono>
#include <cstdlib>
#define size 100

size_t N;
size_t M;
int* arr;
size_t sum[size];

void* add(void* arg) {
	size_t id = *(size_t*)arg;
	size_t start = id * (N/M);
	size_t end = (id == M -1) ? N : start + (N/M);
	size_t s = 0;
	for(size_t i = start; i < end; ++i) {
		s += arr[i];
	}
	sum[id] = s;
	return NULL;
}

int main(int argc, char* argv[]) {
	if(argc != 3) {
		std::cout << "Usage: " << argv[0] << "<N> <M>\n";
		return 1;
	}

	N = std::atol(argv[1]);
	M = std::atoi(argv[2]);
	arr = new int[N];

	srand(time(NULL));
	for(size_t i = 0; i < N; ++i) {
		arr[i] = rand() % 100;
	}

	auto t1 = std::chrono::steady_clock::now();

	size_t sum1 = 0;

	for(size_t i = 0; i < N; ++i) {
		sum1 += arr[i];
	}

	auto t2 = std::chrono::steady_clock::now();
	double time1 = std::chrono::duration<double, std::milli>(t2-t1).count();

        //----------------sum with threads-------------------
	
	pthread_t threads[size];
	size_t id[size];

	auto t3 = std::chrono::steady_clock::now();

	for(size_t i = 0; i < M; ++i) {
		id[i] = i;
		pthread_create(&threads[i], NULL, add, &id[i]);
	}

	for(size_t i = 0; i < M; ++i) {
		pthread_join(threads[i], NULL);
	}

	size_t sum2 = 0;

	for(size_t i = 0; i < M; ++i) {
		sum2 += sum[i];
	}

	auto t4 = std::chrono::steady_clock::now();
	double time2 = std::chrono::duration<double, std::milli>(t4-t3).count();

	std::cout << "Time without threads: " << time1 << "ms\n";
	std::cout << "Time with " << M << "threads: " << time2 << "ms\n";
	delete[] arr;

}
