#include "main.h"

/**
 * tokenize - works with strtok
 * @query: string to tokenize
 * Return: matrix (arr of tokenized strings)
 */
char **tokenize(char *query)
{
	char *token, **tokens;
	int i = 0;

	tokens = malloc(sizeof(char *) * SIZE);
	if (!tokens)
	{
		perror("Malloc Error: ");
		exit(98);
	}
	token = strtok(query, " \t\n");
	while (token)
	{
		tokens[i++] = strdup(token);
		token = strtok(NULL, " \t\n");
	}
	tokens[i] = NULL;
	return (tokens);
}
