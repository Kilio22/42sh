/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** setenv
*/

#include <stdlib.h>
#include <stdio.h>
#include "shell.h"
#include "my_stdio.h"
#include "my_string.h"
#include "my.h"

static char *get_name(char *env)
{
    int i = 0;
    char *str;

    while (env[i] != '=')
        i++;
    str = my_strndup(env, i);
    return (str);
}

static int modif_env(struct my_shell *shell, int i, char *val, char *env_name)
{
    char *new_name = my_strcat_nofree(env_name, "=");

    if (new_name == NULL)
        return -1;
    new_name = my_strcat_freeleft(new_name, val);
    if (new_name == NULL)
        return -1;
    shell->env[i] = my_strdup(new_name);
    if (shell->env[i] == NULL)
        return -1;
    free(new_name);
    return 0;
}

static int new_env(struct my_shell *shell, char *name, char *val)
{
    char *new_name = my_strcat_nofree(name, "=");

    if (new_name == NULL)
        return -1;
    new_name = my_strcat_freeleft(new_name, val);
    if (new_name == NULL)
        return -1;
    shell->env = my_realloc_array(shell->env, new_name);
    if (shell->env == NULL)
        return -1;
    return 0;
}

int set_env(struct my_shell *shell, char *name, char *val)
{
    char *env_name;

    if (is_alphanum(name) == 0) {
        fprintf(stderr, "setenv: Variable name must");
        fprintf(stderr, " contain alphanumeric characters.\n");
        return -1;
    }
    for (int i = 0; shell->env[i] != NULL; i++) {
        env_name = get_name(shell->env[i]);
        if (env_name == NULL)
            continue;
        if (my_strcmp(env_name, name) == 0)
            return modif_env(shell, i, val, env_name);
    }
    return new_env(shell, name, val);
}

int my_setenv(struct my_shell *shell, char **av)
{
    int ac = my_strarraylen(av);

    if (ac == 1)
        my_show_wordarray(shell->env);
    if (ac == 2)
        return set_env(shell, av[1], "");
    if (ac == 3)
        return set_env(shell, av[1], av[2]);
    if (ac > 3)
        fprintf(stderr, "setenv: Too many arguments.\n");
    return -1;
}