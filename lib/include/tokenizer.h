/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** tokenizer
*/

#ifndef TOKENIZER_H_
#define TOKENIZER_H_

#include "delimiters.h"

struct token_node {
    struct token_node *next;
    struct token_node *prev;
    char *content;
    enum delim_ids id;
};

struct token_node *create_token_list_from_line(char *line);

struct token_node *create_token_list_head(void);
struct token_node *create_node(enum delim_ids id, struct token_node *prev);
int add_node(struct token_node *head, enum delim_ids id, char *ptr, ssize_t n);
void delete_token_node_list(struct token_node *head);
void delete_node(struct token_node *ptr);

/* UTILS */
char *slice_string(char **src, size_t index);
char *cut_string(char **src, size_t index);
struct token_node *get_last_node(struct token_node *head);
#define RM_CHAR(str, i) memmove(str + i, str + i + 1, strlen(str) - i)

#endif /* !TOKENIZER_H_ */
