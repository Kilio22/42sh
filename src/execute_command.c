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
    char *tmp = NULL;
    struct token_node *tokens;

    if (!pipe || !pipe->token_list || !pipe->token_list->content)
        return NULL;
    av = malloc(sizeof(char *));
    if (!av)
        exit(84);
    av[0] = NULL;
    tokens = pipe->token_list;
    for (; tokens; tokens = tokens->next) {
        tmp = strdup(tokens->content);
        if (!tmp)
            exit(84);
        av = my_realloc_array(av, tmp);
        if (!av)
            exit(84);
    }
    return av;
}

static pid_t execute_pipe(struct my_shell *shell, struct pipe_s *pipes,
                            char **av, pid_t pgid)
{
    pipes->pid = fork();
    if (pipes->pid < 0)
        return -1;
    if (pipes->pid != 0) {
        if (!pipes->prev)
            pgid = pipes->pid;
        if (setpgid(pipes->pid, pgid) == -1)
            return -1;
    }
    if (pipes->pid == 0) {
        execute_child(shell, pipes, av);
        _exit(1);
    }
    return pgid;
}

static int check_pipes_for_cmd(struct pipe_s *pipes)
{
    int pipefd[2];

    if (pipes->next) {
        if (pipe(pipefd) == -1)
            return fprintf(stderr, "%s.\n", strerror(errno)), -1;
        pipes->fd[1] = pipefd[1];
        pipes->next->fd[0] = pipefd[0];
    }
    return check_redirections_files(pipes);
}

int execute_builtin_in_shell(char **av, struct my_shell *shell,
struct pipe_s *pipes)
{
    int ret;

    ignore_signals(false);
    check_redirections_files(pipes);
    if (setup_io(pipes) == -1)
        return -1;
    ret = execute_builtin(av, shell);
    ignore_signals(true);
    if (dup2(shell->fd_save[0], STDIN_FILENO) == -1)
        return 1;
    if (dup2(shell->fd_save[1], STDOUT_FILENO) == -1)
        return 1;
    if (dup2(shell->fd_save[2], STDERR_FILENO) == -1)
        return 1;
    return ret;
}

pid_t execute_command(struct my_shell *shell, struct pipe_s *pipes, pid_t pgid)
{
    char **av = get_av(pipes);

    if (!av)
        return -1;
    if (is_builtin(av[0]) && !pipes->next)
        return execute_builtin_in_shell(av, shell, pipes);
    while (pipes) {
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
