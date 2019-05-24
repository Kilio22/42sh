/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** execute_command
*/

#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include "my.h"
#include "my_string.h"
#include "parser.h"
#include "shell.h"

char **get_av(struct pipe_s *pipe)
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

bool is_builtin(char *cmd)
{
    if (!cmd)
        exit(1);
    for (ssize_t i = 0; builtins[i]; i++)
        if (!strcmp(cmd, builtins[i]->name))
            return true;
    return false;
}

ssize_t get_builtin_idx(char *cmd)
{
    if (!cmd)
        exit(1);
    for (ssize_t i = 0; builtins[i]; i++)
        if (!strcmp(cmd, builtins[i]->name))
            return i;
    return -1;
}

int exec_builtin(char **av, struct my_shell *shell)
{
    ssize_t idx = get_builtin_idx(av[0]);

    if (idx < 0)
        return -1;
    if (builtins[idx]->ptr(shell, av) == -1) {
        shell->n_return = 2;
        return -1;
    }
    shell->n_return = 0;
    return 0;
}

int restore_path(struct my_shell *shell)
{
    char buffer[1024] = {0};
    size_t len = 0;

    if (confstr(_CS_PATH, buffer, 1024) == 0)
        return -1;
    return my_setenv(shell->env, buffer);
}

char *get_cmd_path(char *cmd, struct my_shell *shell)
{
    char *path = my_getenv(shell, "PATH");
    char **diff_path = NULL;

    if (!path)
        if (restore_path(shell) == -1)
            return NULL;
    path = my_getenv(shell, "PATH");
    diff_path = my_str_towordarray(path, ":");
    for (int i = 0; diff_path[i]; i++) {
        path = my_strcat_nofree(diff_path[i], cmd);
        if (access(path, F_OK))
            return path;
        free(path);
        path = NULL;
    }
    return NULL;
}

int my_execve(char **av, struct my_shell *shell)
{
    //TU CODES ICI;
}

int exec_direct_cmd(char **av, struct my_shell *shell)
{
    if (access(av[0], F_OK) == -1 || access(av[0], X_OK))
        return fprintf(stderr, "%s: Command not found.\n"), -1;
    return my_execve(av, shell);
}

int execute_child(struct my_shell *shell, struct pipe_s *pipes, char **av)
{
    char new_av = NULL;

    if (is_builtin(av[0]))
        exit(exec_builtin(av, shell));
    if (strchr(av[0], '/'))
        return exec_direct_cmd(av, shell);
    new_av = get_cmd_path(av[0], shell);
    if (!new_av) {
        fprintf(stderr, "%s: Command not found.\n", av[0]), -1;
        return -1;
    }
    free(av[0]);
    av[0] = new_av;
    return my_execve(av, shell);
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

void do_right_redirections(struct pipe_s *pipes, int i)
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

void do_left_redirections(struct pipe_s *pipes, int i)
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

int check_pipes(char ***av, struct pipe_s *pipes)
{
    int pipefd[2];

    my_free_fields((*av));
    (*av) = NULL;
    if (pipes->next) {
        if (pipe(pipefd) == -1)
            return -1;
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
        if (check_pipes(&av, pipes) == -1)
            return -1;
        pid = execute_pipe(shell, pipes, av);
        if (shell->n_return != 0)
            return -1;
        pipes = pipes->next;
    }
    return pid;
}
