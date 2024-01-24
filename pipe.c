#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
	printf("Number of command-line arguments: %d\n", argc);

	//print each command line argument
	for(int i = 0; i < argc; i++){
		printf("Argument %d: %s\n", i, argv[i]);
	}

	execlp(argv[1], argv[1], NULL);

	//sanity check
	printf("This line should not be reached.");

	return 0;
}
