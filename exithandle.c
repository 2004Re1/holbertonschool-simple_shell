#include "shell.h"

/**
 * exit_handler - handle exit function
 * @query: query
 * @status: status
 * Return: 0 if exit
 */
int exit_handler(char *query, int *status)
{
	if (strcmp(query, "env") == 0)
	{
		*status = 0;
		print_env(), free(query);
		return (1);
	}
	if (strcmp(query, "exit") == 0)
		free(query), exit(*status);
	return (0);
}
