/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** delete_command
*/

#include <stdlib.h>
#include <unistd.h>
#include "shell.h"

int destroy_pipe(struct pipe_s *p)
{
    struct pipe_s *head = p;

    while (head) {
        p = p->next;
        delete_token_node_list(head->token_list);
        for (int i = 0; i < 6; i++)
            free(head->redirections[i]);
        if (head->fd[0] != STDIN_FILENO && close(head->fd[0]) == -1)
            return -1;
        if (head->fd[1] != STDOUT_FILENO && close(head->fd[1]) == -1)
            return -1;
        if (head->fd[2] != STDERR_FILENO && close(head->fd[2]) == -1)
            return -1;
        free(head);
        head = p;
    }
    return 0;
}

int delete_command(struct cmd_s *cmd)
{
    struct cmd_s *head = cmd;

    while (head) {
        cmd = cmd->next;
        if (destroy_pipe(head->pipe) == -1)
            return -1;
        free(head);
        head = cmd;
    }
    return 0;
}
