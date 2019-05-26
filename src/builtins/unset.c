/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** unset
*/

#include <string.h>
#include <stdlib.h>
#include "my_string.h"
#include "my_stdio.h"
#include "my.h"
#include "shell.h"

static char *get_name(char *env)
{
    int i = 0;
    char *str;

    while (env[i] != ' ' && env[i] != '\t')
        i++;
    str = strndup(env, i);
    return (str);
}

static int find_index(char **env, char *name)
{
    int good_index = -1;
    char *env_name = NULL;

    for (int i = 0; env[i] != NULL; i++) {
        env_name = get_name(env[i]);
        if (env_name == NULL)
            return -2;
        if (strcmp(env_name, name) == 0)
            good_index = i;
    }
    free(env_name);
    return (good_index);
}

static int unset_local(struct my_shell *shell, char *name)
{
    int index = find_index(shell->local_env, name);

    if (index == -2)
        return -1;
    else if (index == -1)
        return 0;
    else {
        shell->local_env = my_remove_ptr_fromarray(shell->local_env,
shell->local_env[index]);
        if (shell->local_env == NULL)
            return -1;
    }
    return 0;
}

int my_unset(struct my_shell *shell, char **av)
{
    int ac = my_strarraylen(av);
    int ret_val = 0;

    if (ac == 1) {
        fprintf(stderr, "unset: Too few arguments.\n");
        return -1;
    }
    for (int i = 1; i < ac; i++) {
        ret_val = unset_local(shell, av[i]);
        if (ret_val == -1)
            return -1;
    }
    return 0;
}