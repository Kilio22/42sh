/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** parser
*/

#ifndef PARSER_H_
#define PARSER_H_

#include "tokenizer.h"

enum cmd_types {
    CMD_NORMAL,
    CMD_OR,
    CMD_AND,
    CMD_NB
};

struct pipe_s {
    struct token_node *token_list;
    char *redirections[6];
    int fd[3];
    pid_t pid;
    struct pipe_s *next;
    struct pipe_s *prev;
};

struct cmd_s {
    struct token_node *token_list;
    enum cmd_types id;
    struct pipe_s *pipe;
    struct cmd_s *next;
    struct cmd_s *prev;
};

struct cmd_s *separate_token_list(struct token_node *head);
int check_syntax(struct token_node *head);
int check_sep(struct token_node *head);
int pipe_parser(struct cmd_s *cmd);
struct cmd_s *get_last_cmd(struct cmd_s *head);
struct cmd_s *delete_separators(struct cmd_s *list);
struct pipe_s *pipe_token_list(struct token_node *token);
struct pipe_s *delete_pipe(struct pipe_s *list);
int check_pipe_redirections(struct pipe_s *pipe);
int check_already_redirect(struct pipe_s *pipe, int idx1, int idx2);
int check_redirections(struct token_node *head, struct pipe_s *pipe);
int check_red_type_conditions_input(struct token_node **token,
struct pipe_s *pipe);
int check_red_type_conditions_output(struct token_node **token,
struct pipe_s *pipe);

#endif /* !PARSER_H_ */