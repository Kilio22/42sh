/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** yes
*/

#include <stdio.h>
#include "my_string.h"
#include "shell.h"

static void print_arg_yes(int argc, char **av, int i)
{
    printf("%s", av[i]);
    if (i + 1 < argc)
        printf(" ");
}

int my_yes(struct my_shell *shell __attribute__((unused)), char **av)
{
    int ac = my_strarraylen(av);
    int i = 1;

    if (ac == 1) {
        while (1)
            printf("y\n");
        return 0;
    }
    while (1) {
        while (i < ac) {
            print_arg_yes(ac, av, i);
            i++;
        }
        i = 1;
        printf("\n");
    }
    return 0;
}