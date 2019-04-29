/*
** EPITECH PROJECT, 2019
** PSU_minishell1_2018
** File description:
** Destroys an environement variable
*/

#include <stdlib.h>
#include "my.h"
#include "my_string.h"
#include "my_stdio.h"
#include "minishell.h"

void unset_everything(my_env_t *env)
{
    my_free_fields(env->env);
    env->blocks = 0;
    env->env = NULL;
}

void unset_env(char **argv, my_env_t *env)
{
    int index;

    if (my_strarraylen(argv) == 1) {
        my_dprintf(2, "unsetenv: Too few arguments.\n");
        return;
    }
    if (my_strcmp(argv[1], "*") == 0)
        return (unset_everything(env));
    for (int i = 1; argv[i] != 0; i++) {
        index = find_var_index(argv[i], env->env);
        if (index == -1)
            continue;
        free(env->env[index]);
        for (; env->env[index] != 0; index++)
            env->env[index] = env->env[index + 1];
        env->blocks++;
    }
}
