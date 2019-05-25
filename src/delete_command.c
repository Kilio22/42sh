/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** delete_command
*/

#include <stdlib.h>
#include <unistd.h>
#include "shell.h"

int destroy_pipe_fds(struct pipe_s *p)
{
    if (p->fd[0] != STDIN_FILENO && close(p->fd[0]) == -1)
        return -1;
    if (p->fd[1] != STDOUT_FILENO && close(p->fd[1]) == -1)
        return -1;
    if (p->fd[1] == p->fd[2])
        return 0;
    if (p->fd[2] != STDERR_FILENO && close(p->fd[2]) == -1)
        return -1;
    return 0;
}

int destroy_pipe(struct pipe_s *p)
{
    struct pipe_s *head = p;

    while (head) {
        p = p->next;
        delete_token_node_list(head->token_list);
        for (int i = 0; i < 6; i++)
            free(head->redirections[i]);
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
