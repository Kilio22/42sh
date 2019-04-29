/*
** EPITECH PROJECT, 2019
** PSU_minishell2_2018
** File description:
** recursive_analysis
*/

#include <wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include "my.h"
#include "my_stdio.h"
#include "my_string.h"
#include "minishell.h"

static char **check_pipes(char ***command_ptr)
{
    size_t len = my_strarraylen(*command_ptr);

    for (size_t i = len - 1; i < len; i--) {
        if (my_strcmp((*command_ptr)[i], "|") == 0) {
            return my_cut_array(command_ptr, i);
        }
    }
    return NULL;
}

static void display_strerror_message(char *str, int fd_in)
{
    if (fd_in == -1)
        my_printf("%s: No such file or directory.\n", str);
}

static char **check_for_redirections(int *fd_in, int *fd_out, char **command)
{
    for (size_t i = 0; command[i]; i++) {
        if (STR_EQ(command[i], ">")) {
            *fd_out = open(command[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0664);
            command = my_remove_ptr_fromarray(command, command[i + 1]);
            command = my_remove_ptr_fromarray(command, command[i--]);
        } else if (STR_EQ(command[i], ">>")) {
            *fd_out = open(command[i + 1], O_WRONLY | O_CREAT | O_APPEND, 0664);
            command = my_remove_ptr_fromarray(command, command[i + 1]);
            command = my_remove_ptr_fromarray(command, command[i--]);
        }
        if (STR_EQ(command[i], "<")) {
            *fd_in = open(command[i + 1], O_RDONLY);
            display_strerror_message(command[i + 1], *fd_in);
            command = my_remove_ptr_fromarray(command, command[i + 1]);
            command = my_remove_ptr_fromarray(command, command[i--]);
        }
    }
    return command;
}

int execute_command(int fd_in, int fd_out, char **command, my_env_t *env)
{
    char **to_pipe;
    int pipefd[2];

    to_pipe = check_pipes(&command);
    command = check_for_redirections(&fd_in, &fd_out, command);
    if (fd_in == -1 || fd_out == -1)
        return -1;
    if (to_pipe) {
        if (pipe(pipefd) == -1)
            return -1;
        if (execute_command(fd_in, pipefd[1], to_pipe, env) == -1)
            return -1;
        close(pipefd[1]);
        fd_in = pipefd[0];
    }
    dup2(fd_in, STDIN_FILENO);
    dup2(fd_out, STDOUT_FILENO);
    close(fd_in);
    close(fd_out);
    return run_command(command, env);
}
