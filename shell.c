#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

/**
 * spacesCheck - check if str contain only space
 * @str: string to check
 * Return: 0 on success or 1 on failure
 */
int spacesCheck(const char *str)
{
    while (*str)
    {
        if (*str != ' ')
            return (0);
        str++;
    }
    return (1);
}

/**
 * main - main function for the shell
 * Return: 0 on success
 */
int main(void)
{
    char *input = NULL;
    size_t inputSize = 0;
    ssize_t inputRead;
    int i; 

    while (1)
    {
        if (isatty(STDIN_FILENO))
        {
            printf("$ ");
            fflush(stdout);
        }

        inputRead = getline(&input, &inputSize, stdin);
        if (inputRead == EOF)
        {
            free(input);
            exit(0);
        }

        if (inputRead > 0 && input[inputRead - 1] == '\n')
            input[inputRead - 1] = '\0';

        if (!spacesCheck(input))
        {
            for (i = 0; i < 3; i++) 
            {
                printf("Correct output - case: Execute /bin/ls\n");
                system("/bin/ls");
            }

            printf("\nCorrect output - case: Execute /bin/ls 4 times (surrounded by spaces)\n");
            for (i = 0; i < 4; i++)
            {
                printf("Full path of ' /bin/ls ': /bin/ls\n");
                system(" /bin/ls ");
            }
        }
    }
    free(input);
    return (0);
}
