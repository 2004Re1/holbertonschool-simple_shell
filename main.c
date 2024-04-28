#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

int _execute(char *arguments, struct stat *statbuf, char**envp);
int check_file_status(char* pathname, struct stat *statbuf);

char **line_div(char *command)
{
	char **arr;
	char *token;
	int i = 0;

	token = strtok(command, " \n\t");
	while (token != NULL && i < 63)
	{
		arr[i++] = token;
		token = strtok(NULL, " \n\t");
	}
	arr[i++] = NULL;
	return (arr);
}

int main(char **env)
{
	char *buff = NULL, *prompt = "$ ";
	size_t buff_size = 0;
	ssize_t bytes;
	pid_t wpid;
	int wstatus;
	int from_pipe = 0;
	struct stat statbuf;

	while(1 && !from_pipe)
	{
		if(isatty(STDIN_FILENO == 0))
			from_pipe = 1;

		printf("%s",prompt);

		bytes = getline(&buff, &buff_size, stdin);
		if(bytes == -1)
		{
			perror("Error (getline)");
			free(buff);
			exit(EXIT_FAILURE);
		}

		if (buff[bytes-1] == '\n')
			buff[bytes-1] = '\0';

		wpid = fork();
		if(wpid == -1)
		{
			perror("Error (fork)");
			exit(EXIT_FAILURE);

		}
		if(wpid == 0)
			_execute(buff, &statbuf, env);

		if(waitpid(wpid, &wstatus, 0) == -1)
		{
			perror("Error (wait)");
			exit(EXIT_FAILURE);
		}

	}
	free(buff);
	return (0);
}

int _execute(char *arguments, struct stat *statbuf, char **envp)
{
	int argc;
	char **argv;
	char *exe;

	argv = line_div(arguments);

	if (!check_file_status(argv[0], statbuf))
	{
		perror("Error (file status)");
		exit(EXIT_FAILURE);
	}
	
	execve(argv[0], argv, envp);

	perror("Error (execve)");
	exit(EXIT_FAILURE);
}

int check_file_status(char *pathname, struct stat *statbuf)
{
	int stat_return;
	stat_return = stat(pathname, statbuf);
	
	if(stat_return == 0)
		return (1);

	return (0);

}
