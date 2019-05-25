/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** env
*/

#include <stdio.h>
#include "shell.h"
#include "my_stdio.h"
#include "my_string.h"

int my_env(struct my_shell *shell, char **av)
{
    int ac = my_strarraylen(av);

    if (ac != 1) {
        fprintf(stderr, "env: '%s': No such file or directory\n", av[1]);
        return -1;
    } else {
        my_show_wordarray(shell->env);
        return 0;
    }
    return (0);
}