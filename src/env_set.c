/*
** EPITECH PROJECT, 2019
** PSU_minishell1_2018
** File description:
** Adds an environrement variable
*/

#include <stdlib.h>
#include "my.h"
#include "my_string.h"
#include "my_stdio.h"
#include "minishell.h"

static int my_char_isalphanum(char c)
{
    if (c >= '0' && c <= '9')
        return 1;
    if (c >= 'a' && c <= 'z')
        return 1;
    if (c >= 'A' && c <= 'Z')
        return 1;
    return 0;
}

static int check_givenvar_isvalid(char *var)
{
    for (int i = 0; var[i] != '\0'; i++) {
        if (my_char_isalphanum(var[i]))
            continue;
        if (var[i] == '_')
            continue;
        return (0);
    }
    return (1);
}

static char *get_var_value(char **argv)
{
    int len = my_strarraylen(argv);

    if (len > 3) {
        my_dprintf(2, "setenv: Too many arguments.\n");
        return (NULL);
    }
    if (!check_givenvar_isvalid(argv[1])) {
        my_dprintf(2,
"setenv: Variable name must contain alphanumeric characters.\n");
        return (NULL);
    }
    if (argv[2] != NULL)
        return (my_strdup(argv[2]));
    else
        return (my_strdup(""));
}

static void update_blocks(my_env_t *env)
{
    if (env->blocks == 0)
        enlarge_env(env);
    env->blocks--;
}

void set_env(char **argv, my_env_t *env)
{
    int index;
    char *var_value;

    if (my_strarraylen(argv) == 1) {
        display_env(argv, env);
        return;
    }
    var_value = get_var_value(argv);
    if (var_value == NULL)
        return;
    update_blocks(env);
    index = find_var_index(argv[1], env->env);
    if (index == -1) {
        index = my_strarraylen(env->env);
        env->env[index + 1] = 0;
    } else
        free(env->env[index]);
    env->env[index] = my_strcat(my_strdup(argv[1]), my_strdup("="));
    env->env[index] = my_strcat(env->env[index], var_value);
}
