#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>
#include <sys/time.h>

#define MAX_COMMAND_LENGTH 1000

int main(int argc, char const *argv[])
{
	pid_t pid;
	// Max command length is assumed to be ceil(len_of_first_command/MAX_COMMAND_LENGTH)
	char command[MAX_COMMAND_LENGTH]="";

	for(int i = 1; i < argc; i++) {
		strcat(command, argv[i]);
		strcat(command, " ");
	}

	pid = fork();
	if(pid == 0) {
		int fd = shm_open("TimeCalculationSharedMem", O_CREAT | O_RDWR, 0666);
		struct timeval *ptr = (struct timeval *)mmap(0, sizeof(struct timeval), PROT_WRITE, MAP_SHARED, fd, 0);
		gettimeofday(ptr, NULL);
		execlp("/bin/sh", "sh", "-c", command, NULL);
	}

	else if(pid > 0) {
		int status;
		struct timeval end;
		wait(&status);
		gettimeofday(&end, NULL);
		int fd = shm_open("TimeCalculationSharedMem", O_RDONLY, 0666);
		struct timeval *start = (struct timeval *)mmap(0, sizeof(struct timeval), PROT_READ, MAP_SHARED, fd, 0);
		printf("Elapsed time: %lf\n", (end.tv_sec - start->tv_sec) + (end.tv_usec - start->tv_usec)/1000000.0);
		shm_unlink("TimeCalculationSharedMem");
	}
}