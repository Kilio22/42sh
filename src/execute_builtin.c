/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** execute_builtins
*/

#include "shell.h"

int execute_builtin(char **av, struct my_shell *shell)
{
    ssize_t idx = get_builtin_idx(av[0]);

    if (idx < 0)
        return -1;
    if (builtins[idx].ptr(shell, av) == -1) {
        shell->n_return = 1;
        return 0;
    }
    shell->n_return = 0;
    return 0;
}
