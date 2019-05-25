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
#include "shell.h"

static char **get_av(struct pipe_s *pipe)
{
    char **av = NULL;
    struct token_node *tokens;

    if (!pipe || !pipe->token_list || !pipe->token_list->content)
        return NULL;
    av = malloc(sizeof(char *));
    if (!av)
        return NULL;
    av[0] = NULL;
    tokens = pipe->token_list;
    for (; tokens; tokens = tokens->next) {
        av = my_realloc_array(av, strdup(tokens->content));
        if (!av)
            return NULL;
    }
    return av;
}

pid_t execute_pipe(struct my_shell *shell, struct pipe_s *pipes, char **av,
                    pid_t pgid)
{
    pipes->pid = fork();
    if (pipes->pid < 0)
        return -1;
    if (pipes->pid != 0) {
        if (!pipes->prev)
            pgid = pipes->pid;
        setpgid(pipes->pid, pgid);
    }
    if (pipes->pid == 0) {
        execute_child(shell, pipes, av);
        _exit(1);
    }
    return pgid;
}

int check_pipes_for_cmd(struct pipe_s *pipes)
{
    int pipefd[2];

    if (pipes->next) {
        if (pipe(pipefd) == -1)
            return fprintf(stderr, "%s.\n", strerror(errno)), -1;
        pipes->fd[1] = pipefd[1];
        pipes->next->fd[0] = pipefd[0];
    }
    check_redirections_files(pipes);
    return 0;
}

int execute_builtin_in_shell(char **av, struct my_shell *shell,
struct pipe_s *pipes)
{
    ignore_signals(false);
    check_redirections_files(pipes);
    if (setup_io(pipes) == -1)
        return 0;
    if (builtins[get_builtin_idx(av[0])].ptr(shell, av) == -1)
        shell->n_return = 1;
    if (dup2(shell->fd_save[0], STDIN_FILENO) == -1)
        return fprintf(stderr, "%s\n", strerror(errno));
    if (dup2(shell->fd_save[0], STDOUT_FILENO) == -1)
        return fprintf(stderr, "%s\n", strerror(errno));
    if (dup2(shell->fd_save[0], STDERR_FILENO) == -1)
        return fprintf(stderr, "%s\n", strerror(errno));
    ignore_signals(true);
    return 0;
}

pid_t execute_command(struct my_shell *shell, struct pipe_s *pipes, pid_t pgid)
{
    char **av = get_av(pipes);

    if (!av)
        return -1;
    while (pipes) {
        if (is_builtin(av[0]) && !pipes->next)
            return execute_builtin_in_shell(av, shell, pipes);
        if (check_pipes_for_cmd(pipes) == -1)
            return -1;
        pgid = execute_pipe(shell, pipes, av, pgid);
        if (destroy_pipe_fds(pipes) == -1)
            return -1;
        pipes = pipes->next;
        my_free_fields(av);
        av = get_av(pipes);
    }
    return pgid;
}
