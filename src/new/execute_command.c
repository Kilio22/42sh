/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** execute_command
*/

#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <fcntl.h>
#include "my.h"
#include "my_string.h"
#include "parser.h"
#include "shell.h"

static char **get_av(struct pipe_s *pipe)
{
    char **av = NULL;
    struct token_node *tokens;

    if (!pipe)
        return NULL;
    av = malloc(sizeof(char *));
    if (!av)
        return NULL;
    av[0] = NULL;
    tokens = pipe->token_list;
    for (; tokens; tokens = tokens->next) {
        av = my_realloc_array(av, tokens->content);
        if (!av)
            return NULL;
    }
    return av;
}

pid_t execute_pipe(struct my_shell *shell, struct pipe_s *pipes, char **av)
{
    pid_t pid = fork();

    if (pid < 0)
        return -1;
    if (pid == 0)
        execute_child(shell, pipes, av);
    return pid;
}

int check_pipes_for_cmd(char ***av, struct pipe_s *pipes)
{
    int pipefd[2];

    my_free_fields((*av));
    (*av) = NULL;
    if (pipes->next) {
        if (pipe(pipefd) == -1)
            return fprintf(stderr, strerror(errno)), -1;
        pipes->fd[1] = pipefd[1];
        pipes->next->fd[0] = pipefd[0];
    }
    check_redirections_files(pipes);
    (*av) = get_av(pipes);
    if (!(*av))
        return -1;
    return 0;
}

pid_t execute_command(struct my_shell *shell, struct pipe_s *pipes, pid_t pgid)
{
    int pipefd[2];
    pid_t pid;
    int n_return = 0;
    char **av = get_av(pipes);

    if (!av)
        return -1;
    if (is_builtin(av[0]) && !pipes->next)
        return exec_builtin(av, shell);
    while (pipes) {
        if (check_pipes_for_cmd(&av, pipes) == -1)
            return -1;
        pid = execute_pipe(shell, pipes, av);
        if (shell->n_return != 0)
            return -1;
        pipes = pipes->next;
    }
    return pid;
}
