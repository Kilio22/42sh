/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** yes
*/

#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include "my_string.h"
#include "shell.h"

static void print_arg_yes(int argc, char **av, int i)
{
    write(1, av[i], strlen(av[i]));
    if (i + 1 < argc)
        putchar(' ');
}

int my_yes(struct my_shell *shell __attribute__((unused)), char **av)
{
    int ac = my_strarraylen(av);
    int i = 1;

    if (ac == 1) {
        while (1)
            puts("y");
        return 0;
    }
    while (1) {
        while (i < ac) {
            print_arg_yes(ac, av, i);
            i++;
        }
        i = 1;
        putchar('\n');
    }
    return 0;
}