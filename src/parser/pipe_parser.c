/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** pipe_parser
*/

#include <stdio.h>
#include <stdlib.h>
#include "tokenizer.h"
#include "parser.h"

int check_pipe(struct token_node *head)
{
    for (; head; head = head->next) {
        if (head->id != ID_PIPE)
            continue;
        if (!head->prev || !head->next)
            return fprintf(stderr, "Invalid null command.\n"),-1;
    }
    return 0;
}

int pipe_parser(struct cmd_s *cmd)
{
    for (; cmd; cmd = cmd->next) {
        if (check_pipe(cmd->token_list) == -1)
            return -1;
        cmd->pipe = pipe_token_list(cmd->token_list);
    }
    return 0;
}