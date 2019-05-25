/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** flag_parsing
*/

#include "my_string.h"
#include "echo.h"

void init_echo(echo_t *params)
{
    params->newline = true;
    params->backslash = true;
    params->first_str = 1;
}

void parse_flags(echo_t *params, int ac, char **av)
{
    int i = 1;

    if (ac == 1)
        return;
    if (my_strlen(av[i]) != 2)
        return;
    if (my_strcmp("-n", av[i]) != 0)
        return;
    params->first_str++;
    params->newline = false;
}