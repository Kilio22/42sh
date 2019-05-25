/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** my_execve
*/

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "shell.h"

void my_execve(struct my_shell *shell, struct pipe_s *pipes, char **av,
                char *bin_name)
{
    char *bonus = "";

    if (setup_io(pipes) == -1)
        _exit(1);
    execve(bin_name, av, shell->env);
    if (errno == ENOEXEC)
        bonus = " Wrong Architecture.";
    fprintf(stderr, "%s: %s.%s\n", bin_name, strerror(errno), bonus);
    free(bin_name);
    _exit(1);
}
