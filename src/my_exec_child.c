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
        return fprintf(stderr, "%s: Command not found.\n", av[0]), -1;
    return my_execve(shell, p, av);
}

int execute_child(struct my_shell *shell, struct pipe_s *pipes, char **av)
{
    char *new_av = NULL;

    // ! remettre les signaux
    if (is_builtin(av[0]))
        exit(execute_builtin(av, shell));
    if (strchr(av[0], '/'))
        return exec_direct_cmd(shell, pipes, av);
    new_av = get_cmd_path(av[0], shell);
    if (!new_av)
        return fprintf(stderr, "%s: Command not found.\n", av[0]), -1;
    free(av[0]);
    av[0] = new_av;
    return my_execve(shell, pipes, av);
}