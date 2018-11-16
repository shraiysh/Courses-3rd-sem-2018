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
	int fd = shm_open("TimeCalculationSharedMem", O_RDONLY, 0666);
	struct timeval *start = (struct timeval *)mmap(0, sizeof(struct timeval), PROT_READ, MAP_SHARED, fd, 0);
	gettimeofday(start, NULL);
	printf("start=%ld", start->tv_sec);
	shm_unlink("TimeCalculationSharedMem");

}