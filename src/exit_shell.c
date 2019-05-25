/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** exit_shell
*/

#include <stdlib.h>
#include <unistd.h>
#include "shell.h"

void exit_shell(struct my_shell *shell, unsigned char exit_code)
{
    if (isatty(STDIN_FILENO))
        puts("exit");
    destroy_my_shell(shell);
    exit(exit_code);
}
