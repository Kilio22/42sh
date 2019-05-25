/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** do_redirections
*/

#include <fcntl.h>
#include "parser.h"
#include "shell.h"

static void do_right_redirections(struct pipe_s *pipes, int i)
{
    int fd;

    if (i <= 1)
        fd = open(pipes->redirections[i], O_CREAT | O_RDWR | O_APPEND, 0664);
    else
        fd = open(pipes->redirections[i], O_CREAT | O_RDWR | O_TRUNC, 0664);
    if (fd == -1) {
        fprintf(stderr, "Redirection failed.\n");
        return;
    }
    pipes->fd[1] = fd;
}

static void do_left_redirections(struct pipe_s *pipes, int i)
{
    int fd;

    if (i >= 5)
        fd = open(pipes->redirections[i], O_CREAT | O_RDWR | O_APPEND, 0664);
    else
        fd = open(pipes->redirections[i], O_CREAT | O_RDWR | O_TRUNC, 0664);
    if (fd == -1) {
        fprintf(stderr, "Redirection failed.\n");
        return;
    }
    pipes->fd[0] = fd;
}

void check_redirections_files(struct pipe_s *pipes)
{
    for (int i = 0; i < 6; i++) {
        if (!pipes->redirections[i])
            continue;
        else if (i <= 4)
            do_right_redirections(pipes, i);
        else
            do_left_redirections(pipes, i);
    }
}