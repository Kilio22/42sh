/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** parser_utils
*/

#include <stdlib.h>
#include "tokenizer.h"
#include "parser.h"

struct cmd_s *get_last_cmd(struct cmd_s *head)
{
    if (!head)
        return NULL;
    while (head->next)
        head = head->next;
    return head;
}

int check_already_redirect(struct pipe_s *pipe, int idx1, int idx2)
{
    for (int i = idx1; i < idx2; i++)
        if (pipe->redirections[i])
            return -1;
    return 0;
}