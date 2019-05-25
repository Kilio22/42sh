/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** echo
*/

#include <stdbool.h>

#ifndef ECHO_H_
#define ECHO_H_

typedef struct echo_s {
    bool newline;
    bool backslash;
    int first_str;
} echo_t;

void init_echo(echo_t *params);
void parse_flags(echo_t *params, int ac, char **av);

#endif /* !ECHO_H_ */
