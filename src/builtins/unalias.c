/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** unalias
*/

#include <stdio.h>
#include <stdlib.h>
#include "my_string.h"
#include "shell.h"

static void unalias_all(struct alias_s alias[MAX_ALIAS])
{
    for (int i = 0; i < MAX_ALIAS; i++) {
        if (alias[i].name == NULL)
            continue;
        free(alias[i].name);
        free(alias[i].command);
        alias[i].name = NULL;
    }
}

static int unalias(struct alias_s alias[MAX_ALIAS], int index)
{
    int last_index = 0;
    char *tmp;

    for (; last_index < 400; last_index++)
        if (alias[last_index].name == NULL)
            break;
    last_index--;
    tmp = alias[last_index].name;
    alias[last_index].name = alias[index].name;
    alias[index].name = tmp;
    tmp = alias[last_index].command;
    alias[last_index].command = alias[index].command;
    alias[index].command = tmp;
    free(alias[last_index].name);
    free(alias[last_index].command);
    alias[last_index].name = NULL;
    alias[last_index].command = NULL;
    return 0;
}

int my_unalias(struct my_shell *shell, char **av)
{
    int alias_ind;
    int ac = my_strarraylen(av);

    if (ac == 1) {
        fprintf(stderr, "unalias: Too few arguments.\n");
        return -1;
    }
    for (int i = 1; i < ac; i++) {
        if (my_strcmp("*", av[i]) == 0) {
            unalias_all(shell->aliases);
            return 0;
        }
        alias_ind = find_alias(shell->aliases, av[i]);
        if (alias_ind == -1 || shell->aliases[alias_ind].name == NULL)
            continue;
        if (unalias(shell->aliases, alias_ind) == -1) {
            fprintf(stderr, "unalias: error.\n");
            return -1;
        }
    }
    return 0;
}