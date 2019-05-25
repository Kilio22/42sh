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

static int setup_io(struct pipe_s *pipes)
{
    if (pipes->fd[0] != STDIN_FILENO) {
        if (dup2(pipes->fd[0], STDIN_FILENO) == -1)
            return -1;
        close(pipes->fd[0]);
    }
    if (pipes->fd[1] != STDOUT_FILENO) {
        if (dup2(pipes->fd[1], STDOUT_FILENO) == -1)
            return -1;
        close(pipes->fd[1]);
    }
    if (pipes->fd[2] != STDERR_FILENO) {
        if (dup2(pipes->fd[2], STDERR_FILENO) == -1)
            return -1;
        close(pipes->fd[2]);
    }
    return 0;
}

int my_execve(struct my_shell *shell, struct pipe_s *pipes, char **av,
                char *bin_name)
{
    char *bonus = "";

    if (setup_io(pipes) == -1)
        return -1;
    execve(bin_name, av, shell->env);
    if (errno == ENOEXEC)
        bonus = " Wrong Architecture.";
    fprintf(stderr, "%s: %s.%s\n", bin_name, strerror(errno), bonus);
    free(bin_name);
    exit(1);
    return -1;
}
