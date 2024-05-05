#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define MAX_LINE 1024

/*
 * main - function for the simple shell program
 *        
 *
 * Return: EXIT_SUCCESS on successful execution, EXIT_FAILURE on failure.
 */

int main(void) {
    char line[MAX_LINE];
    pid_t pid;
    int status;

    while (1) {
        // Display the prompt
        printf("#cisfun$ ");
        
        // Read the command line
        if (fgets(line, MAX_LINE, stdin) == NULL) {
            // Handle end of file (Ctrl+D)
            printf("\n");
            break;
        }

        // Replace newline character with null terminator
        line[strcspn(line, "\n")] = '\0';

        // Fork a child process
        pid = fork();

        if (pid == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            // Child process: execute the command
            if (execlp(line, line, (char *)NULL) == -1) {
                // If the executable cannot be found, print an error message
                perror("execlp");
                exit(EXIT_FAILURE);
            }
        } else {
            // Parent process: wait for the child to finish
            waitpid(pid, &status, 0);
        }
    }

    return EXIT_SUCCESS;
}

