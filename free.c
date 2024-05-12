#include "shell.h"

/**
 * matrix_freear - frees matrix
 * @matrix: matrix to free
 */
void matrix_freear(char **matrix)
{
	int i = 0;

	while (matrix[i])
		free(matrix[i++]);
	free(matrix);
}
