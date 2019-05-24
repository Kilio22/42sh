/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** builtins
*/

#include <stdio.h>
#include "builtins.h"
#include "my_string.h"

int display_builtins(struct my_shell *shell __attribute__((unused)), char **av)
{
    int ac = my_strarraylen(av);

    if (ac != 1) {
        fprintf(stderr, "builtins: too much arguments\n");
    }
    for (int i = 0; i < 16; i++) {
        my_printf("%s", my_builtins[i][0]);
        if (my_strlen(my_builtins[i][0]) < 8)
            my_printf("\t");
        my_printf(" :\t%s\n", my_builtins[i][1]);
    }
    return 0;
}