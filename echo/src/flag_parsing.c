/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** flag_parsing
*/

#include "echo.h"

void init_echo(echo_t *params)
{
    params->newline = true;
    params->backslash = false;
    params->first_str = 1;
}

static void manage_flag(char c, echo_t *params)
{
    if (c == 'e')
        params->backslash = true;
    else if (c == 'n')
        params->newline = false;
    else
        params->backslash = false;
}

void parse_flags(echo_t *params, int ac, char *av[])
{
    int i = 1;

    for (; i < ac; i++) {
        if (my_strlen(av[i]) != 2)
            break;
        if (av[i][0] != '-')
            break;
        if (av[i][1] != 'e' && av[i][1] != 'E' && av[i][1] != 'n')
            break;
        params->first_str++;
        manage_flag(av[i][1], params);
    }
}