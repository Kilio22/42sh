/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** repeat
*/

#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <wait.h>
#include <string.h>
#include "my_string.h"
#include "my_stdio.h"
#include "shell.h"

static char *join_command(char **av)
{
    char *str = strdup(av[0]);

    if (!str)
        return NULL;
    for (size_t i = 1; av[i]; i++) {
        str = my_strcat(str, strdup(" "));
        if (!str)
            return NULL;
        str = my_strcat(str, strdup(av[i]));
        if (!str)
            return NULL;
    }
    return str;
}

int my_repeat(struct my_shell *shell, char **av)
{
    size_t ac = my_strarraylen(av);
    ssize_t count;
    char *str = NULL;
    ret_t ret;

    if (ac < 3)
        return fprintf(stderr, "repeat: Too few arguments.\n"), 1;
    count = strtol(av[1], &str, 10);
    if (str && *str)
        return fprintf(stderr, "repeat: Badly formed number.\n"), 1;
    str = join_command(av + 2);
    if (!str)
        _exit(1);
    ignore_signals(true);
    while (count--)
        ret = execute_line(shell, str);
    ignore_signals(false);
    return ret;
}
