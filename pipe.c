#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{ 

	printf("argc length: %d\n", argc);

	if (argc == 2){
		printf("this line should only run if there is 1 command provided.\n");
		if (execlp(argv[1], argv[1], NULL) == -1) {
            perror("execlp");
            exit(1);
        }
	}

	int fds[2];

	for (int i = 1; i < argc; i++){

		if (i != argc - 1){ //if last cmd, don't create pipe (skip this step)		
			printf("creating pipe\n");
			if (pipe(fds) == -1){  // creates a pipe, the pipefd passed inside will be. pipefd[0] is the read end, pipefd[1] is the write end
				perror("pipe");
				exit(EXIT_FAILURE);
			};	
		}
		
		int child_pid = fork();

		if (child_pid == -1) {
			perror("fork");
			exit(1);
		}


		// child processs 
		if (child_pid == 0){
			// redirect input from STDIN to reading from old pipe (all except first case )

			printf("Iteration: %d (child).\n", i);

			printf("Running command : %s\n", argv[i]);

			if (i != 1){
				dup2(fds[0], STDIN_FILENO);
				printf("redirect input from STDIN to reading from old pipe\n");
			} 
			

			// redirect output to pipe (all except last case)
			if(i != argc - 1){
				dup2(fds[1], STDOUT_FILENO); //redirect command's output from standard output -> pipe buffer
				printf("redirect output from stdout to pipe\n");
			}
			
			close(fds[0]); //closes read (not needed)
			close(fds[1]); //no longer needed 

			
	
			execlp(argv[i], argv[i], NULL); //run cmd 1
		}
		else if (child_pid > 0){

			printf("Iteration: %d (parent).\n", i);

			dup2(fds[0], STDIN_FILENO); //redirect input of second arg to take in from pipe buffer 
			close(fds[1]); //close write (not needed)
			close(fds[0]); //no longer needed 
			
			wait(NULL);
		}
		printf("Iteration : %d finished.\n", i);
	}

	
	return 0;
}