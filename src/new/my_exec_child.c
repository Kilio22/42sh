/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** my_exec_child
*/

#include <stdio.h>
#include <unistd.h>
#include "shell.h"
#include "parser.h"

static int exec_direct_cmd(char **av, struct my_shell *shell)
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