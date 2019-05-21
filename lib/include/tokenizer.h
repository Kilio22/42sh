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
    enum delimiter_ids id;
};

struct token_node *create_node(int id, char *content);
void add_node(struct token_node *head, int id, char *content);
void delete_token_node_list(struct token_node *head);
void delete_node(struct token_node *ptr);

/* UTILS */
char *slice_string(char **src, size_t index);
char *cut_string(char **src, size_t index);

#endif /* !TOKENIZER_H_ */
