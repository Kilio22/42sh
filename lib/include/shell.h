/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** shell
*/

#ifndef SHELL_H_
#define SHELL_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include "enums.h"
#include "defines.h"

typedef unsigned char ret_t;

struct my_shell {
    char **env;
    int fd_save[FD_SAVE_NB];
    ret_t n_return;
};

/* Shell manipulation */
struct my_shell *create_my_shell(char const *env[]);
void destroy_my_shell(struct my_shell *shell);
void exit_shell(struct my_shell *shell, unsigned char exit_code);

/* Command execution */
int loop_shell(struct my_shell *shell);
int execute_line(struct my_shell *shell, char *line);
int execute_command(struct my_shell *shell, struct cmd_s *command);

/* Useful functions (maybe) */
char *my_getenv(struct my_shell *shell, const char *name);
ssize_t my_getenv_index(struct my_shell *shell, const char *name);
char *get_line(FILE *f_stream);

#endif /* !SHELL_H_ */
