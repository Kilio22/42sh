/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** disp_alias
*/

#include <stdio.h>
#include "shell.h"

void display_aliases(struct alias_s alias[MAX_ALIAS])
{
    for (int i = 0; i < MAX_ALIAS; i++) {
        if (alias[i].name == NULL)
            break;
        printf("%s\t%s\n", alias[i].name, alias[i].command);
    }
}

void display_one_alias(struct alias_s alias[MAX_ALIAS], char *name)
{
    int index = find_alias(alias, name);

    if (index == -1 || alias[index].name == NULL)
        return;
    printf("%s\n", alias[index].command);
}

int full_alias(void)
{
    fprintf(stderr, "alias: Too many aliases.\n");
    return -1;
}