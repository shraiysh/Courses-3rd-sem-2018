#include <iostream>
#include <algorithm>
#include <cmath>

double mean, median, std_dev;
int N;

pthread_t mean_worker, median_worker, std_dev_worker;

void *mean_func(void *param);
void *median_func(void *param);
void *std_dev_func(void *param);

int main() {

	mean = median = std_dev = 0;

	std::cin >> N;

	double *my_array = new double[N];
	for(int i = 0; i < N; i++)
		std::cin >> my_array[i];
	
	pthread_attr_t attr;
	pthread_attr_init(&attr);

	pthread_create(&mean_worker, &attr, mean_func, my_array);
	pthread_create(&median_worker, &attr, median_func, my_array);
	pthread_create(&std_dev_worker, &attr, std_dev_func, my_array);

	pthread_join(median_worker, NULL);
	pthread_join(std_dev_worker, NULL);		// This worker makes sure that the mean_worker stops.
	std::cout << "The average value is " << mean << std::endl;
	std::cout << "The standard deviation value is " << std_dev << std::endl;
	std::cout << "The median value is " << median << std::endl;

	delete[] my_array;
}

void *mean_func(void *param) {
	double *my_array = (double *)param;
	mean = 0;
	for(int i=0; i < N; i++) {
		mean += my_array[i] / N;
	}
}

void *median_func(void *param) {
	// A temporary array to store sorted array
	double *my_array = (double *)param;
	double *temp_copy = new double[N];
	std::copy(my_array, my_array + N, temp_copy);
	std::sort(temp_copy, temp_copy + N);
	
	if(N % 2 == 1) median = temp_copy[N / 2];
	else median = (temp_copy[N / 2] + temp_copy[N / 2 - 1]) / 2.0;
	
	delete[] temp_copy;
}

void *std_dev_func(void *param) {
	double *my_array = (double *)param;
	double mean_x2 = 0;

	for(int i = 0; i < N; i++) {
		mean_x2 += (my_array[i] * my_array[i]) / N;
	}

	pthread_join(mean_worker, NULL);
	std_dev = sqrt(mean_x2 - mean * mean) * sqrt(N * 1.0 / (N - 1));
}