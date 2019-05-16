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

void init_echo(echo_t *params)
{
    params->newline = true;
    params->backslash = false;
    params->first_str = 1;
}

void manage_flag(char c, echo_t *params)
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

int loop_parsing_flags(char *str, int index)
{
    char flags[] = "\\abefnrtv";
    char outputs[] = "\\\a\b\e\f\n\r\t\v";

    for (int i = 0; i < 9; i++) {
        if (str[index] == flags[i]) {
            my_putchar(outputs[i]);
            return 1;
        }
    }
    return 0;
}

void parse_str_and_print(echo_t *params, char *str)
{
    int i = 0;

    (void) params;
    while (str[i] != '\0') {
        if (str[i] == '\\' && str[i + 1] == 'c') {
            params->first_str = -1;
            return;
        }
        if (loop_parsing_flags(str, i) == 1) {
            i += 2;
            continue;
        }
        my_putchar(str[i]);
        i++;
    }
}

void print_strings(echo_t *params, int ac, char *av[])
{
    int i = params->first_str;

    for (; i < ac; i++) {
        if (params->first_str == -1)
            return;
        if (i != params->first_str)
            my_putchar(' ');
        if (params->backslash == true)
            parse_str_and_print(params, av[i]);
        else
            my_putstr(av[i]);
    }
}

void echo(int ac, char *av[])
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

int main(int ac, char *av[])
{
    echo(ac, av);
    return (0);
}
