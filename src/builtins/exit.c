/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** exit
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "my_stdio.h"
#include "my_string.h"
#include "my.h"
#include "shell.h"

void exit_shell(struct my_shell *shell, ret_t ret_val)
{
    free_alias(shell->aliases);
    destroy_my_shell(shell);
    if (isatty(STDIN_FILENO) == 1)
        my_printf("exit\n");
    exit(ret_val);
}

static int check_exit_code(char *ret_val)
{
    if (my_str_isnum(ret_val, true) == false) {
        if (ret_val[0] != '-' && (ret_val[0] < '0' || ret_val[0] > '9'))
            fprintf(stderr, "exit: Expression Syntax.\n");
        else
            fprintf(stderr, "exit: Badly formed number.\n");
        return -1;
    }
    return 0;
}

int my_exit(struct my_shell *shell, char **av)
{
    int ac = my_strarraylen(av);

    if (ac == 1)
        exit_shell(shell, shell->n_return);
    else if (ac == 2) {
        if (check_exit_code(av[1]) == -1)
            return -1;
        exit_shell(shell, atoi(av[1]));
    } else {
        fprintf(stderr, "exit: Expression Syntax.\n");
        return -1;
    }
    return 0;
}