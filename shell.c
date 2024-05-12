#include "main.h"
/**
 * main - entry point to shell
 * Return: 0 on success
 */
int main(void)
{
	char *query, *temp = NULL;
	int r, status = 0, tty;
	size_t size;

	while (true)
	{
		query = NULL;
		tty = isatty(STDIN_FILENO);
		if (tty)
			printf("#cisfun$ ");
		fflush(stdout);
		r = getline(&query, &size, stdin);
		if (r == -1)
		{
			if (tty == 1)
				printf("\n");
			free(query);
			break;
		}
		query[r - 1] = 0, temp = query;
		if (query == NULL)
		{
			free(temp);
			break;
		}
		while (query[0] == 32 || query[0] == '\t')
			query++;

		if (query[0] == '\n' || query[0] == 0)
		{
			free(temp);
			continue;
		}
		if (exit_handler(query, &status))
			continue;
		query_formatter(query, temp, &status);
	}
	return (status);
}
