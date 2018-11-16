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

int main(int argc, char const *argv[])
{
	char *command[argc];
	for (int i = 1; i < argc; ++i) {
		command[i-1] = malloc(sizeof(argv[i]));
		strcpy(command[i-1], argv[i]);
	}
	command[argc-1] = NULL;

	struct timeval *start, end;
	int status, fd;

	pid_t pid = fork();
	
	if(pid == 0) {
		fd = shm_open("OS", O_CREAT | O_RDWR, 0666);
		ftruncate(fd, sizeof(struct timeval));
		start = (struct timeval *)mmap(0, sizeof(struct timeval), PROT_WRITE, MAP_SHARED, fd, 0);
		gettimeofday(start, NULL);
		execvp(command[0], command);
	}
	else if(pid > 0) {
		wait(&status);
		gettimeofday(&end, NULL);
		if(status == 0) {
			// Correct execution of child!
			fd = shm_open("OS", O_RDONLY, 0666);
			start = (struct timeval *) mmap(0, sizeof(struct timeval), PROT_READ, MAP_SHARED, fd, 0);
			printf("Elapsed time: %lf\n", (end.tv_sec - start->tv_sec) + (end.tv_usec - start->tv_usec)/1000000.0);
		}
		// shm_unlink("OS");
	}
}