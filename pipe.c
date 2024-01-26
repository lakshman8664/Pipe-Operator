#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
	// base case for only 1 argument 
	if (argc == 2){
		if (execlp(argv[1], argv[1], NULL) == -1) {
            perror("execlp");
            exit(1);
        }
	}

	int fds[2];		// initialize an integer array of size 2
	pipe(fds);	// creates a pipe, the pipefd passed inside will be 
                      // modified to store the read/write fd of the pipe
                      // pipefd[0] is the read end, pipefd[1] is the write end

	for(int i = 1; i < argc + 1; i++){
		int pid = fork();

		//if fork() failed, throw error 
		if (pid == -1) {
			perror("fork");
			exit(1);
		}
		// child processs 
		if (pid == 0){
			dup2(fds[1], STDOUT_FILENO); //redirect command's output from standard output -> pipe buffer

			close(fds[0]); //closes read (not needed)

			close(fds[1]); //no longer needed 
			
			execlp(argv[i], argv[i], NULL); //run cmd 1
		}
		else if (pid > 0){

			dup2(fds[0], STDIN_FILENO); //redirect input of second arg to take in from pipe buffer 

			close(fds[1]); //close write (not needed)
			close(fds[0]); //no longer needed 

			execlp(argv[i+1], argv[i+1], NULL); //run cmd 2

			wait(NULL); //wait for child process to finish

		}
	}


	return 0;
}
