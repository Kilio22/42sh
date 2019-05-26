/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** set
*/

#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include "my_string.h"
#include "my_stdio.h"
#include "my.h"
#include "builtins.h"

static char *get_name(char *env)
{
    int i = 0;
    char *str;

    while (env[i] != ' ' && env[i] != '\t')
        i++;
    str = strndup(env, i);
    return (str);
}

static int modif_env(struct my_shell *shell, int i, char *val, char *env_name)
{
    char *new_name = my_strcat_nofree(env_name, "\t");

    if (new_name == NULL)
        return -1;
    new_name = my_strcat_freeleft(new_name, val);
    if (new_name == NULL)
        return -1;
    shell->local_env[i] = strdup(new_name);
    if (shell->local_env[i] == NULL)
        return -1;
    free(new_name);
    return 0;
}

static int new_env(struct my_shell *shell, char *name, char *val)
{
    char *new_name = my_strcat_nofree(name, "\t");

    if (new_name == NULL)
        return -1;
    new_name = my_strcat_freeleft(new_name, val);
    if (new_name == NULL)
        return -1;
    shell->local_env = my_realloc_array(shell->local_env, new_name);
    if (shell->local_env == NULL)
        return -1;
    return 0;
}

int set_local(struct my_shell *shell, char *name, char *val)
{
    char *env_name;

    for (int i = 0; shell->local_env[i] != NULL; i++) {
        env_name = get_name(shell->local_env[i]);
        if (env_name == NULL)
            continue;
        if (strcmp(env_name, name) == 0)
            return modif_env(shell, i, val, env_name);
    }
    return new_env(shell, name, val);
}

int my_set(struct my_shell *shell, char **av)
{
    int ac = my_strarraylen(av);
    char *val = NULL;

    if (ac == 1)
        my_show_wordarray(shell->local_env);
    for (int i = 1; av[i]; i++) {
        if (!is_alpha(av[i][0])) {
            fprintf(stderr, "set: Variable name must begin with a letter.\n");
            return -1;
        }
        val = get_val(av[i]);
        if (!val)
            continue;
        set_local(shell, av[i], val);
    }
    return -1;
}