/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** builtins
*/

#include <stdio.h>
#include "shell.h"
#include "my_string.h"
#include "my_stdio.h"
#include "shell.h"

int display_builtins(struct my_shell *shell __attribute__((unused)), char **av)
{
    int ac = my_strarraylen(av);

    if (ac != 1) {
        fprintf(stderr, "builtins: too much arguments\n");
    }
    for (int i = 0; builtins[i].name != NULL; i++) {
        my_printf("%s", builtins[i].name);
        if (my_strlen(builtins[i].name) < 8)
            my_printf("\t");
        my_printf(" :\t%s\n", builtins[i].desc);
    }
    return 0;
}