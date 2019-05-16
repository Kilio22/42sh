/*
** EPITECH PROJECT, 2018
** main.c
** File description:
** Main function
*/

#include <stdbool.h>
#include "my_stdio.h"
#include "echo.h"
#include "my.h"

void init_echo(echo_t *params)
{
    params->newline = true;
    params->backslash = false;
}

void echo(int ac, char *av[])
{
    echo_t params;

    init_echo(&params);
    if (ac == 0) {
        my_putstr("\n");
        return;
    }
}

int main(int ac, char *av[])
{
    echo(ac, av);
    return (0);
}
