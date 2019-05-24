/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** whoami
*/

#include <stdlib.h>
#include <stdio.h>
#include "my_string.h"
#include "builtins.h"

int my_whoami(struct my_shell *shell, char **av)
{
    int ac = my_strarraylen(av);
    char *whoami = getlogin();

    if (ac != 1) {
        fprintf(stderr, "whoami: too much arguments\n");
        return -1;
    }
    if (whoami == NULL)
        return -1;
    printf("%s\n", whoami);
    return 0;
}