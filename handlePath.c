#include "main.h"

/**
 * get_path - gets path of a query
 * @matrix: argv
 * @query: query
 * Return: path of the query
*/
char *get_path(char **matrix, char *query)
{
	struct stat st;
	char *path = getenv("PATH"), *copyenv = NULL, *token = NULL, *f_path = NULL;

	if (path == NULL || strlen(path) == 0)
	{
		fprintf(stderr, "./hsh: 1: %s: not found\n", matrix[0]);
		free(query), matrix_freear(matrix);
		exit(127);
	}
	copyenv = strdup(path), token = strtok(copyenv, ":");
	f_path = malloc(sizeof(char) * SIZE);
	while (token != NULL)
	{
		snprintf(f_path, SIZE, "%s/%s", token, matrix[0]);
		if (stat(f_path, &st) == 0)
		{
			free(copyenv);
			return (f_path);
		}
		token = strtok(NULL, ":");
	}
	fprintf(stderr, "./hsh: 1: %s: not found\n", matrix[0]);
	free(query), free(copyenv), free(f_path), matrix_freear(matrix);
	exit(127);
}
