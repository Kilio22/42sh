/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** my_getenv
*/

#include <string.h>
#include "shell.h"

static size_t my_varlen(const char *s)
{
    const char *char_ptr = s;

    if (!s)
        return (-1);
    while (*char_ptr && *char_ptr != '=')
        char_ptr++;
    return (char_ptr - s);
}

char *my_getenv(struct my_shell *shell, const char *name)
{
    size_t namelen = strlen(name);
    size_t len;

    for (size_t i = 0; shell->env[i]; i++) {
        len = my_varlen(shell->env[i]);
        if (namelen > len)
            len = namelen;
        if (!strncmp(name, shell->env[i], len))
            return shell->env[i] + len + 1;
    }
    return NULL;
}
