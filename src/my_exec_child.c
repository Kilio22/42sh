/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** my_exec_child
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "shell.h"

static int exec_direct_cmd(struct my_shell *shell, struct pipe_s *p, char **av)
{
    if (access(av[0], F_OK) == -1)
        return fprintf(stderr, "%s: Command not found.\n", av[0]), 1;
    return my_execve(shell, p, av, av[0]), 1;
}

void execute_child(struct my_shell *shell, struct pipe_s *pipes, char **av)
{
    char *bin_name = NULL;

    ignore_signals(false);
    if (is_builtin(av[0]))
        _exit(execute_builtin(av, shell));
    if (strchr(av[0], '/'))
        _exit(exec_direct_cmd(shell, pipes, av));
    bin_name = get_cmd_path(av[0], shell);
    if (!bin_name) {
        fprintf(stderr, "%s: Command not found.\n", av[0]);
        destroy_my_shell(shell);
        _exit(1);
    }
    my_execve(shell, pipes, av, bin_name);
}