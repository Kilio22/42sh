/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** destroy_my_shell
*/

#include <stdlib.h>
#include <unistd.h>
#include "my.h"
#include "shell.h"

void destroy_my_shell(struct my_shell *shell)
{
    my_free_fields(shell->env);
    my_free_fields(shell->local_env);
    close(shell->fd_save[SAVE_STDIN]);
    close(shell->fd_save[SAVE_STDOUT]);
    close(shell->fd_save[SAVE_STDERR]);
    free(shell);
}
