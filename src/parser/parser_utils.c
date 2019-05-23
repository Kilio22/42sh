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