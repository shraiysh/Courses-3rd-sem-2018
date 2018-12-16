#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <algorithm>
#include <cmath>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>

int main() {
	int N;
	std::cin >> N;
	
	double *my_array = new double[N];

	for(int i = 0; i < N; i++) {
		std::cin >> my_array[i];
	}

	pid_t pid1 = fork();
	pid_t pid2 = fork();

	int fd;

	if(pid1 > 0 && pid2 > 0) {
		// Process 1 - waits for the other processes to join
		waitpid(pid1, NULL, 0);
		waitpid(pid2, NULL, 0);
		// Read mean
		fd = shm_open("mean", O_RDONLY, 0666);
		double *mean = (double *)mmap(0, sizeof(double), PROT_READ, MAP_SHARED, fd, 0);
		fd = shm_open("median", O_RDONLY, 0666);
		double *median = (double *)mmap(0, sizeof(double), PROT_READ, MAP_SHARED, fd, 0);
		fd = shm_open("std_dev", O_RDONLY, 0666);
		double *std_dev = (double *)mmap(0, sizeof(double), PROT_READ, MAP_SHARED, fd, 0);

		std::cout << "The average value is " << *mean << std::endl;
		std::cout << "The standard deviation value is " << *std_dev << std::endl;
		std::cout << "The median value is " << *median << std::endl;

		shm_unlink("mean");
		shm_unlink("median");
		shm_unlink("std_dev");
	}

	if(pid1 == 0 && pid2 > 0) {
		// Process 2 - child of process 1 - calculates standard deviation

		// Shared memory for storing std_dev
		fd = shm_open("std_dev", O_CREAT | O_RDWR, 0666);
		ftruncate(fd, sizeof(double));
		double *std_dev = (double *)mmap(0, sizeof(double), PROT_WRITE, MAP_SHARED, fd, 0);
		
		// First calculate mean of x^2
		double mean_x2 = 0;

		for(int i = 0 ; i < N; i++)
			mean_x2 += (my_array[i] * my_array[i]) / N;

		waitpid(pid2, NULL, 0);		// Wait for mean

		// Read mean from shared memory
		fd = shm_open("mean", O_RDONLY, 0666);
		double *mean = (double *)mmap(0, sizeof(double), PROT_READ, MAP_SHARED, fd, 0);
		
		*std_dev = sqrt(mean_x2 - (*mean) * (*mean)) * sqrt(N * 1.0 / (N-1));
	}

	if(pid1 > 0 && pid2 == 0) {
		// Another child of process 1 - Calculates median

		// Create shared memory for median
		fd = shm_open("median", O_CREAT | O_RDWR, 0666);
		ftruncate(fd, sizeof(double));
		double *median = (double *)mmap(0, sizeof(double), PROT_WRITE, MAP_SHARED, fd, 0);

		// A temporary array to store sorted array
		double *temp_copy = new double[N];
		std::copy(my_array, my_array + N, temp_copy);
		std::sort(temp_copy, temp_copy + N);
		
		if(N % 2 == 1) *median = temp_copy[N/2];
		else *median = (temp_copy[N/2] + temp_copy[N/2-1])/2.0;
		
		delete[] temp_copy;
	}

	if(pid1 == 0 && pid2 == 0) {

		// Child of process 2 -> Grandchild of process 1 - Calculate mean

		// Create shared memory to store mean
		fd = shm_open("mean", O_CREAT | O_RDWR, 0666);
		ftruncate(fd, sizeof(double));
		double *mean = (double *)mmap(0, sizeof(double), PROT_WRITE, MAP_SHARED, fd, 0);

		*mean = 0;
		for(int i=0; i < N; i++)
			*mean += my_array[i]/N;
	}

	delete[] my_array;
	return 0;
}