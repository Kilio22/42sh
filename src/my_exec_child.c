/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** my_exec_child
*/

#include <stdio.h>
#include <unistd.h>
#include <wait.h>
#include <stdlib.h>
#include <string.h>
#include "shell.h"

static int exec_direct_cmd(struct my_shell *shell, char **av)
{
    if (access(av[0], F_OK) == -1)
        return fprintf(stderr, "%s: Command not found.\n", av[0]), 1;
    return my_execve(shell, av, av[0]), 1;
}

static ret_t execute_parenthesises(struct my_shell *shell, struct pipe_s *pipes)
{
    pid_t pid = fork();
    int wstatus;

    if (pid == -1)
        return 1;
    if (pid == 0) {
        shell->fd_save[0] = pipes->fd[0];
        shell->fd_save[1] = pipes->fd[1];
        shell->fd_save[2] = pipes->fd[2];
        _exit(execute_line(shell, pipes->token_list->content));
    } else
        waitpid(pid, &wstatus, 0);
    return analyse_exit_status(wstatus);
}

void execute_child(struct my_shell *shell, struct pipe_s *pipes, char **av)
{
    char *bin_name = NULL;

    if (setup_io(pipes) == -1)
        _exit(1);
    if (pipes->token_list->id == ID_PARENTHESIS)
        _exit(execute_parenthesises(shell, pipes));
    ignore_signals(false);
    if (is_builtin(av[0]))
        _exit(execute_builtin(av, shell));
    if (strchr(av[0], '/'))
        _exit(exec_direct_cmd(shell, av));
    bin_name = get_cmd_path(av[0], shell);
    if (!bin_name) {
        fprintf(stderr, "%s: Command not found.\n", av[0]);
        destroy_my_shell(shell);
        _exit(1);
    }
    my_execve(shell, av, bin_name);
}