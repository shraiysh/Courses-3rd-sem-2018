#include <stdio.h>
#include <stdlib.h>
int main(int argc, char *argv[]) {

	int n = 400;
	n = atoi(argv[1]);
	printf("%d\n", n);
	for(int i=0; i < n; i++)
		printf("%f \n", (rand() % 1000) * (rand()%1000)/207.0);
}