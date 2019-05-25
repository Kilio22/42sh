/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** exit
*/

#include <unistd.h>
#include <stdlib.h>
#include "shell.h"

int builtin_exit(struct my_shell *shell, void *cmd)
{
    exit_shell(shell, 0);
    return 0;
}
