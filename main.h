#ifndef SHELL_H
#define SHELL_H

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/types.h>

#define SIZE 100

extern char **environ;

int main(void);
int exit_handler(char *command, int *status);
void query_formatter(char *command, char *temp, int *status);
void execute(char **arr, char *path, int *status, char *temp);
char **tokenize(char *input);
void matrix_freear(char **arr);
void print_env(void);
char *get_path(char **arr, char *command);

#endif /* SHELL_H */
