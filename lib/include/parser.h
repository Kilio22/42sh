/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** parser
*/

#ifndef PARSER_H_
#define PARSER_H_

#include "tokenizer.h"

struct cmd_s {
    struct token_node *token_list;
    enum delim_ids id;
    //struct pipe_s *pipe;
    struct cmd_s *next;
    struct cmd_s *prev;
};

struct cmd_s *separate_token_list(struct token_node *head);
int check_syntax(struct token_node *head);
int check_sep(struct token_node *head);

#endif /* !PARSER_H_ */
 