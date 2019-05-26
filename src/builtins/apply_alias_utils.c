/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** apply_alias_utils
*/

#include <string.h>
#include <stdlib.h>
#include "shell.h"
#include "my_string.h"
#include "my.h"

char *free_and_dup_command(char **command, int index,
struct alias_s aliases[MAX_ALIAS])
{
    char *str;

    free(*command);
    str = strdup(aliases[index].command);
    return str;
}

void free_tab(char **tab)
{
    if (!tab)
        return;
    for (int i = 0; tab[i] != NULL; i++)
        free(tab[i]);
    free(tab);
}

bool is_in_touched(char *name, char **touched)
{
    if (touched == NULL)
        return false;
    for (int i = 0; touched[i] != NULL; i++)
        if (strcmp(name, touched[i]) == 0)
            return true;
    return false;
}