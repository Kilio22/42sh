/*
** EPITECH PROJECT, 2019
** PSU_minishell2_2018
** File description:
** exit_shell
*/

#include <unistd.h>
#include <stdlib.h>
#include "my.h"
#include "my_stdio.h"
#include "minishell.h"

void exit_shell(char **argv, my_env_t *env)
{
    unsigned char exit_code = 0;

    if (argv != NULL) {
        if (argv[1] != NULL && my_str_isnum(argv[1], 0))
            exit_code = my_atoi(argv[1]);
    }
    if (isatty(0))
        my_puts("exit");
    (void) exit_code;
    (void) env;
}
