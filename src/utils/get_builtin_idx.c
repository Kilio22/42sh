/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** get_builtin_idx
*/

#include <sys/types.h>
#include <string.h>
#include <stdlib.h>
#include "shell.h"

ssize_t get_builtin_idx(char *cmd)
{
    for (ssize_t i = 0; builtins[i].name; i++)
        if (!strcmp(cmd, builtins[i].name))
            return i;
    return -1;
}