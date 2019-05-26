/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** do_redirections
*/

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "my_string.h"
#include "shell.h"

static int do_right_redirections(struct pipe_s *pipes, int i)
{
    int fd;

    if (i <= 1)
        fd = open(pipes->redirections[i], O_CREAT | O_RDWR | O_APPEND, 0664);
    else
        fd = open(pipes->redirections[i], O_CREAT | O_RDWR | O_TRUNC, 0664);
    if (fd == -1) {
        fprintf(stderr, "%s: %s\n", pipes->redirections[i], strerror(errno));
        return -1;
    }
    pipes->fd[1] = fd;
    if (i == 0 || i == 2)
        pipes->fd[2] = fd;
    return 0;
}

static char *get_input_line(void)
{
    char *line = NULL;

    if (isatty(STDIN_FILENO))
        write(STDOUT_FILENO, "? ", 2);
    line = get_line(stdin);
    return line;
}

static int do_db_lredir(struct pipe_s *pipes, int i)
{
    int pipefd[2];
    char *line = NULL;
    ssize_t len;
    char *full_line = get_input_line();

    if (!full_line || !strcmp(full_line, pipes->redirections[i]))
        return 0;
    full_line = my_strcat_freeleft(full_line, "\n");
    while ((line = get_input_line()) != NULL &&
strcmp(line, pipes->redirections[i])) {
        full_line = my_strcat(full_line, line);
        full_line = my_strcat_freeleft(full_line, "\n");
    }
    len = strlen(full_line);
    if (pipe(pipefd) == -1 || write(pipefd[1], full_line, len) != len)
        return fprintf(stderr, "%s.\n", strerror(errno)), -1;
    if (close(pipefd[1]) == -1)
        return fprintf(stderr, "%s.\n", strerror(errno)), -1;
    pipes->fd[0] = pipefd[0];
    free(full_line);
    return 0;
}

static int do_left_redirections(struct pipe_s *pipes, int i)
{
    int fd;

    if (i == 4)
        return do_db_lredir(pipes, i);
    fd = open(pipes->redirections[i], O_RDONLY);
    if (fd == -1) {
        fprintf(stderr, "%s: %s\n", pipes->redirections[i], strerror(errno));
        return -1;
    }
    pipes->fd[0] = fd;
    return 0;
}

int check_redirections_files(struct pipe_s *pipes)
{
    int n_val = 0;

    for (int i = 0; i < 6; i++) {
        if (!pipes->redirections[i])
            continue;
        else if (i < 4)
            n_val = do_right_redirections(pipes, i);
        else
            n_val = do_left_redirections(pipes, i);
        if (n_val != 0)
            return -1;
    }
    return 0;
}