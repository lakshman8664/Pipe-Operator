#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
	// printf("Number of command-line arguments: %d\n", argc);

	// //print each command line argument
	// for(int i = 0; i < argc; i++){
	// 	printf("Argument %d: %s\n", i, argv[i]);
	// }

	// execlp(argv[1], argv[1], NULL);

	int fds[2];		// initialize an integer array of size 2
	pipe(fds);	// creates a pipe, the pipefd passed inside will be 
                      // modified to store the read/write fd of the pipe
                      // pipefd[0] is the read end, pipefd[1] is the write end

	int pid = fork();
	if (pid == -1) {
        perror("fork");
        exit(1);
    }
	// child processs 
	if (pid == 0){
		dup2(fds[1], STDOUT_FILENO); //redirect command's output from standard output -> pipe buffer

		close(fds[0]); //closes read (not needed)

		close(fds[1]); //no longer needed 
		
		execlp(argv[1], argv[1], NULL); //run cmd 1
	}
	else if (pid > 0){

		dup2(fds[0], STDIN_FILENO); //redirect input of second arg to take in from pipe buffer 

		close(fds[1]); //close write (not needed)
		close(fds[0]); //no longer needed 

		execlp(argv[2], argv[2], NULL); //run cmd 2

		wait(NULL);

	}

	return 0;
}
