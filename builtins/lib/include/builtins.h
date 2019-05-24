/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** builtins
*/

#ifndef BUILTINS_H_
#define BUILTINS_H_

#define MAX_ALIAS 400

struct alias_s {
    char *name;
    char *command;
};

struct my_shell {
    char **env;
    int fd_save[FD_SAVE_NB];
    ret_t n_return;
    struct alias_s aliases[MAX_ALIAS];
};

extern const char *my_builtins[][2];

int full_alias(void);
void free_path(char **path);
bool is_a_builtin(const char *str);
int find_var_index(char *var, char **env);
int echo(struct my_shell *shell, char **av);
int my_yes(struct my_shell *shell, char **av);
int my_which(int argc, char **av, char **env);
int my_where(struct my_shell *shell, char **av);
int my_whoami(struct my_shell *shell, char **av);
int my_alias(struct my_shell *shell, char *av[]);
void free_alias(struct alias_s alias[MAX_ALIAS]);
void init_alias(struct alias_s alias[MAX_ALIAS]);
int my_unalias(struct my_shell *shell, char **av);
void display_aliases(struct alias_s alias[MAX_ALIAS]);
int find_alias(struct alias_s alias[MAX_ALIAS], char *name);
char *my_strcat_freeleft(const char *left, const char *right);
void display_one_alias(struct alias_s alias[MAX_ALIAS], char *name);
int display_builtins(struct my_shell *shell __attribute__((unused)), char **av);

#endif /* !BUILTINS_H_ */
