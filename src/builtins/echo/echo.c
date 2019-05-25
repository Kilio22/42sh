/*
** EPITECH PROJECT, 2018
** main.c
** File description:
** Main function
*/

#include <stdbool.h>
#include "my_stdio.h"
#include "shell.h"
#include "my_string.h"
#include "my.h"

static int loop_print_flags(char *str, int index)
{
    char flags[] = "\\abefnrtv";
    char outputs[] = "\\\a\b\e\f\n\r\t\v";

    for (int i = 0; i < 9; i++) {
        if (str[index] == '\\' && str[index + 1] == flags[i]) {
            my_putchar(outputs[i]);
            return 1;
        }
    }
    return 0;
}

static void parse_str_and_print(echo_t *params, char *str)
{
    int i = 0;

    while (str[i] != '\0') {
        if (str[i] == '\\' && str[i + 1] == 'c') {
            params->first_str = -1;
            return;
        }
        if (loop_print_flags(str, i) == 1) {
            i += 2;
            continue;
        }
        my_putchar(str[i]);
        i++;
    }
}

static void print_strings(echo_t *params, int ac, char **av)
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

int echo(struct my_shell *shell __attribute__((unused)), char **av)
{
    echo_t params;
    int ac = my_strarraylen(av);

    init_echo(&params);
    if (ac == 1) {
        my_putstr("\n");
        return 0;
    }
    parse_flags(&params, ac, av);
    print_strings(&params, ac, av);
    if (params.newline == true && params.first_str != -1)
        my_putchar('\n');
    return 0;
}
