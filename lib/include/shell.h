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
    char **local_env;
    int fd_save[FD_SAVE_NB];
    ret_t n_return;
    pid_t pgid;
    struct alias_s aliases[MAX_ALIAS];
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
void exit_shell(struct my_shell *shell, ret_t ret_val);

/* Command execution */
int loop_shell(struct my_shell *shell);
ret_t execute_line(struct my_shell *shell, char *line);
pid_t execute_command(struct my_shell *shell, struct pipe_s *pipes, pid_t pgid);
void execute_child(struct my_shell *shell, struct pipe_s *pipes, char **av);
void my_execve(struct my_shell *shell, char **av, char *bin_name);
int setup_io(struct pipe_s *pipes);
/* ...after execution */
ret_t get_command_status(struct my_shell *shell, struct pipe_s *p, pid_t pgid);
int analyse_exit_status(int wstatus);

/* Useful functions (maybe) */
char *my_getenv(struct my_shell *shell, const char *name);
char *my_get(struct my_shell *shell, const char *name);
ssize_t my_getenv_index(struct my_shell *shell, const char *name);
char *get_line(FILE *f_stream);
int set_foreground_pgrp(pid_t pgrp);
void ignore_signals(bool flag);
int env_variables_token(struct token_node *token, struct my_shell *shell);
int env_variables_loop(struct token_node *token, struct my_shell *shell);

/* Builtins */
ssize_t get_builtin_idx(char *cmd);
bool is_builtin(char *cmd);
ret_t execute_builtin(char **av, struct my_shell *shell);

/* Redirections */
int check_redirections_files(struct pipe_s *pipes);

/* PATH managment */
char *get_cmd_path(char *cmd, struct my_shell *shell);

/* Destroy stuff */
int destroy_pipe(struct pipe_s *p);
int delete_command(struct cmd_s *cmd);
int destroy_pipe_fds(struct pipe_s *p);

#endif /* !SHELL_H_ */
