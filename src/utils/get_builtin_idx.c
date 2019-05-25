/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** get_builtin_idx
*/

#include <sys/types.h>
#include "shell.h"

ssize_t get_builtin_idx(char *cmd)
{
    if (!cmd)
        exit(1);
    for (ssize_t i = 0; builtins[i]; i++)
        if (!strcmp(cmd, builtins[i]->name))
            return i;
    return -1;
}