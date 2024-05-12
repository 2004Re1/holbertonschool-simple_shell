#include "main.h"

/**
 * execute - executes a query
 * @matrix: argv
 * @path: path of the query
 * @status: status
 * @temp: temp
*/
void execute(char **matrix, char *path, int *status, char *temp)
{
	pid_t pid = fork();

	if (pid == -1)
		free(temp), perror("Error");
	else if (pid == 0)
	{
		if (execve(path, matrix, environ) == -1)
		{
			perror("Error execve");
			matrix_freear(matrix);
			free(temp);
			free(path);
			exit(1);
		}
	}
	else
	{
		waitpid(pid, status, 0);
		if (WIFEXITED(*status))
			*status = WEXITSTATUS(*status);
		free(temp);
	}
	free(path);
	matrix_freear(matrix);
}
