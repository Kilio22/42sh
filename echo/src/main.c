/*
** EPITECH PROJECT, 2018
** main.c
** File description:
** Main function
*/

#include <stdbool.h>
#include "my_stdio.h"
#include "echo.h"
#include "my_string.h"
#include "my.h"

static void print_strings(echo_t *params, int ac, const char *av[])
{
    int i = params->first_str;

    for (; i < ac; i++) {
        if (params->first_str == -1)
            return;
        if (i != params->first_str)
            my_putchar(' ');
        my_putstr(av[i]);
    }
}

void echo(int ac, const char *av[])
{
    echo_t params;

    init_echo(&params);
    if (ac == 1) {
        my_putstr("\n");
        return;
    }
    parse_flags(&params, ac, av);
    print_strings(&params, ac, av);
    if (params.newline == true && params.first_str != -1)
        my_putchar('\n');
}

int main(int ac, const char *av[])
{
    echo(ac, av);
    return (0);
}
