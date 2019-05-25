/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** pipe_parser
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "tokenizer.h"
#include "parser.h"

int check_parentheses(struct pipe_s *pipe)
{
    struct token_node *head;

    if (!pipe)
        return 0;
    head = pipe->token_list;
    while (head) {
        if (head->id == ID_PARENTHESIS && ((head->prev && (head->prev->id <
ID_DB_FULL_RREDIRECTION || head->prev->id > ID_LREDIRECTION))
|| head->next))
            return fprintf(stderr, "Badly placed ()'s.\n"), -1;
        head = head->next;
    }
    return 0;
}

int check_pipe(struct token_node *head)
{
    for (; head; head = head->next) {
        if (head->id != ID_PIPE)
            continue;
        if (!head->prev || !head->next)
            return fprintf(stderr, "Invalid null command.\n"), -1;
    }
    return 0;
}

int check_pipe_redirections(struct pipe_s *pipe)
{
    for (; pipe; pipe = pipe->next) {
        if (check_redirections(pipe->token_list, pipe) == -1)
            return -1;
    }
    return 0;
}

int pipe_parser(struct cmd_s *cmd)
{
    for (; cmd; cmd = cmd->next) {
        cmd->pipe = pipe_token_list(cmd->token_list);
        if (check_pipe_redirections(cmd->pipe) == -1)
            return -1;
        if (cmd->pipe)
            cmd->token_list = cmd->pipe->token_list;
        if (check_pipe(cmd->token_list) == -1)
            return -1;
        if (check_parentheses(cmd->pipe) == -1)
            return -1;
    }
    return 0;
}