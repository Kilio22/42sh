/*
** EPITECH PROJECT, 2019
** PSU_minishell2_2018
** File description:
** loop_shell
*/

#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include "my.h"
#include "my_stdio.h"
#include "my_string.h"
#include "minishell.h"

void restore_fd(int fd_in, int fd_out)
{
    if (dup2(fd_in, 0) == -1)
        exit(84);
    if (dup2(fd_out, 1) == -1)
        exit(84);
}

static void destroy_commands(char ***commands)
{
    for (size_t i = 0; commands[i]; i++)
        my_free_fields(commands[i]);
    free(commands);
}

static void wait_last_pid(pid_t pid)
{
    int wstatus;

    if (pid <= 0)
        return;
    if (waitpid(pid, &wstatus, 0) == -1)
        return;
    if (WIFEXITED(wstatus))
        return;
    if (WIFSIGNALED(wstatus))
        display_error_message(WTERMSIG(wstatus));
}

void loop_shell(my_env_t *env)
{
    char ***commands;
    int fd_in = dup(STDIN_FILENO);
    int fd_out = dup(STDOUT_FILENO);
    pid_t pid;

    if (!env || fd_in == -1 || fd_out == -1)
        exit(84);
    while (1) {
        commands = get_commands(env);
        if (check_if_commands_syntax_valid(commands) == false) {
            destroy_commands(commands);
            continue;
        }
        for (size_t i = 0; commands[i]; i++) {
            pid = execute_command(dup(fd_in), dup(fd_out), commands[i], env);
            restore_fd(fd_in, fd_out);
            wait_last_pid(pid);
        }
        free(commands);
    }
}
