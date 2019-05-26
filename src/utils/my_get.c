/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** my_get
*/

#include <stdlib.h>
#include <string.h>
#include "shell.h"

static size_t my_varlen(const char *s)
{
    const char *char_ptr = s;

    if (!s)
        return (-1);
    while (*char_ptr && *char_ptr != ' ' && *char_ptr != '\t')
        char_ptr++;
    return (char_ptr - s);
}

char *my_get(struct my_shell *shell, const char *name)
{
    size_t namelen = strlen(name);
    size_t len;

    for (size_t i = 0; shell->local_env[i]; i++) {
        len = my_varlen(shell->local_env[i]);
        if (namelen > len)
            len = namelen;
        if (!strncmp(name, shell->local_env[i], len))
            return shell->local_env[i] + len + 1;
    }
    return NULL;
}
