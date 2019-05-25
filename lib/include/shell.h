/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** shell
*/

#ifndef SHELL_H_
#define SHELL_H_

#include <sys/types.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include "enums.h"
#include "defines.h"
#include "parser.h"

struct my_shell;

#include "builtins.h"

typedef unsigned char ret_t;

struct my_shell {
    char **env;
    int fd_save[FD_SAVE_NB];
    ret_t n_return;
    pid_t pgid;
    struct alias_s aliases[MAX_ALIAS];
    struct breakpoints_s *history;
};

struct builtins_s {
    char *name;
    char *desc;
    int (*ptr)(struct my_shell *, char **);
};

extern const struct builtins_s builtins[];
extern const char *constants_sig[];

/* Shell manipulation */
struct my_shell *create_my_shell(char const **env);
void destroy_my_shell(struct my_shell *shell);
void exit_shell(struct my_shell *shell, unsigned char exit_code);

/* Command execution */
int loop_shell(struct my_shell *shell);
int execute_line(struct my_shell *shell, char *line);
pid_t execute_command(struct my_shell *shell, struct pipe_s *pipes, pid_t pgid);
ret_t get_command_status(struct my_shell *shell, struct pipe_s *p, pid_t pgid);
int execute_child(struct my_shell *shell, struct pipe_s *pipes, char **av);
int my_execve(struct my_shell *shell, struct pipe_s *pipes, char **av, char *path);

/* Useful functions (maybe) */
char *my_getenv(struct my_shell *shell, const char *name);
ssize_t my_getenv_index(struct my_shell *shell, const char *name);
char *get_line(FILE *f_stream);
int set_foreground_pgid(pid_t pgid);

/* Builtins */
ssize_t get_builtin_idx(char *cmd);
bool is_builtin(char *cmd);
int execute_builtin(char **av, struct my_shell *shell);

/* Redirections */
int check_redirections_files(struct pipe_s *pipes);

/* PATH managment */
char *get_cmd_path(char *cmd, struct my_shell *shell);

#endif /* !SHELL_H_ */
