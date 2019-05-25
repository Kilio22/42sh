/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** utils_alias
*/

#include <stdlib.h>
#include "shell.h"
#include "my_string.h"

void free_alias(struct alias_s alias[MAX_ALIAS])
{
    for (int i = 0; i < MAX_ALIAS; i++) {
        if (alias[i].name != NULL)
            free(alias[i].name);
        if (alias[i].command != NULL)
            free(alias[i].command);
    }
}

void init_alias(struct alias_s alias[MAX_ALIAS])
{
    int i = 0;

    for (; i < MAX_ALIAS; i++) {
        alias[i].name = NULL;
        alias[i].command = NULL;
    }
}

int find_alias(struct alias_s alias[MAX_ALIAS], char *name)
{
    int i = 0;

    for (; i < MAX_ALIAS; i++) {
        if (alias[i].name == NULL)
            return i;
        if (my_strcmp(name, alias[i].name) == 0)
            return i;
    }
    return -1;
}