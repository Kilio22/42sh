/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** setup_io
*/

#include <unistd.h>
#include "shell.h"

int setup_io(struct pipe_s *pipes)
{
    if (pipes->fd[0] != STDIN_FILENO) {
        if (dup2(pipes->fd[0], STDIN_FILENO) == -1)
            return -1;
        if (close(pipes->fd[0]) == -1)
            return -1;
    }
    if (pipes->fd[1] != STDOUT_FILENO) {
        if (dup2(pipes->fd[1], STDOUT_FILENO) == -1)
            return -1;
        if (pipes->fd[1] != pipes->fd[2] && close(pipes->fd[1]) == -1)
            return -1;
    }
    if (pipes->fd[2] != STDERR_FILENO) {
        if (dup2(pipes->fd[2], STDERR_FILENO) == -1)
            return -1;
        if (close(pipes->fd[2]) == -1)
            return -1;
    }
    return 0;
}
