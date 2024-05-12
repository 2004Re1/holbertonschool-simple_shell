#include "main.h"

/**
 * query_formatter - formats query
 * @query: query to execute
 * @temp: temp
 * @status: status
 */
void query_formatter(char *query, char *temp, int *status)
{
	struct stat st;
	char **matrix, *path;

	matrix = tokenize(query);
	if (query[0] == '/' || query[0] == '.')
	{
		if (stat(matrix[0], &st) != 0)
		{
			matrix_freear(matrix), free(temp);
			return;
		}
		path = strdup(query);
	}
	else
		path = get_path(matrix, query);
	execute(matrix, path, status, temp);
}
