/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** builtins
*/

#include <stdbool.h>
#include "shell.h"
#include "echo.h"

#ifndef BUILTINS_H_
#define BUILTINS_H_

#define MAX_ALIAS 400
#define TOO_MANY_CD "cd: Too many arguments.\n"

struct alias_s {
    char *name;
    char *command;
};

int full_alias(void);
int is_alphanum(char *str);
void free_path(char **path);
bool is_a_builtin(const char *str);
int find_var_index(char *var, char **env);
int echo(struct my_shell *shell, char **av);
int my_yes(struct my_shell *shell, char **av);
int my_which(struct my_shell *shell, char **av);
int my_where(struct my_shell *shell, char **av);
int my_whoami(struct my_shell *shell, char **av);
int my_alias(struct my_shell *shell, char **av);
void free_alias(struct alias_s alias[MAX_ALIAS]);
void init_alias(struct alias_s alias[MAX_ALIAS]);
int my_setenv(struct my_shell *shell, char **av);
int set_env(struct my_shell *shell, char *name, char *val);
int my_unalias(struct my_shell *shell, char **av);
int my_unsetenv(struct my_shell *shell, char **av);
void display_aliases(struct alias_s alias[MAX_ALIAS]);
int find_alias(struct alias_s alias[MAX_ALIAS], char *name);
char *my_strcat_freeleft(const char *left, const char *right);
void display_one_alias(struct alias_s alias[MAX_ALIAS], char *name);
int display_builtins(struct my_shell *shell, char **av);
int correct_price(struct my_shell *shell, char **av);
int snake(struct my_shell *shell, char **av);
int my_env(struct my_shell *shell, char **av);
int my_cd(struct my_shell *shell, char **av);
int loop_apply_alias(struct token_node **node,
struct alias_s aliases[MAX_ALIAS]);
int my_exit(struct my_shell *shell, char **av);
int is_alphanumeric(char c);
int my_set(struct my_shell *shell, char **av);
int set_local(struct my_shell *shell, char *name, char *val);
char *get_val(char *arg);
int my_unset(struct my_shell *shell, char **av);
int my_str_isalpha(char *str);
int is_alpha(char c);
void free_tab(char **tab);
bool is_in_touched(char *name, char **touched);
char *free_and_dup_command(char **command, int index,
struct alias_s aliases[MAX_ALIAS]);
int my_repeat(struct my_shell *shell, char **av);

#endif /* !BUILTINS_H_ */
