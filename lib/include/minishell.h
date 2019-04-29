/*
** EPITECH PROJECT, 2019
** PSU_minishell1_2018
** File description:
** Header file for the minishell 1 project
*/

#ifndef MINISHELL_H_
#define MINISHELL_H_

#define ENV_EXTRASIZE 10
#define DEFAULT_HOME "/"
#define DEFAULT_PATH "/usr/local/bin:/usr/bin:/bin:/usr/local/sbin:/usr/sbin"

#include <stddef.h>
#include <stdbool.h>

extern const char *CHAR_WORDS;

typedef struct my_environement_s {
    char **env;
    int blocks;
} my_env_t;

/* PROMPT */
char *read_prompt(void);
char *separate_words(char *line);
char **get_prompt(my_env_t *env);
char ***get_commands(my_env_t *env);

bool check_if_commands_syntax_valid(char ***commands);

int execute_command(int fd_in, int fd_out, char **command, my_env_t *env);

char **my_cut_array(char ***src, size_t index);

void free_env(my_env_t *env);
void loop_shell(my_env_t *env);
void enlarge_env(my_env_t *env);
void update_new_pwd(my_env_t *env);
void update_previous_pwd(my_env_t *env);
my_env_t *init_my_env(char *real_env[]);
void set_env(char **argv, my_env_t *env);
int find_var_index(char *var, char **env);
void unset_env(char **argv, my_env_t *env);
void exit_shell(char **argv, my_env_t *env);
void display_env(char **argv, my_env_t *env);
char **my_str_to_path_array(char const *str);
int execute_prompt(char **argv, my_env_t *env);
void change_active_dir(char **argv, my_env_t *env);
void restore_var_path(my_env_t *env, char *var, char *restore);
void display_error_message(int sig);
int run_command(char **command, my_env_t *env);

typedef struct function_ptrs_s {
    const char *name;
    void (*f_ptr)(char **, my_env_t *);
} my_funcptrs_t;

extern const my_funcptrs_t builtins[5];

#endif /* !MINISHELL_H_ */
