/*
** EPITECH PROJECT, 2019
** PSU_minishell2_2018
** File description:
** run_commands
*/

#include "my.h"
#include "my_string.h"
#include "minishell.h"

static int execute_builtins(char **argv, my_env_t *env)
{
    for (int i = 0; i < 5; i++) {
        if (my_strcmp(argv[0], (builtins[i]).name) == 0) {
            (builtins[i]).f_ptr(argv, env);
            return 1;
        }
    }
    return 0;
}

int run_command(char **command, my_env_t *env)
{
    int n_pid = 0;

    if (!execute_builtins(command, env))
        n_pid = execute_prompt(command, env);
    my_free_fields(command);
    return n_pid;
}
