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

#endif /* !TOKENIZER_H_ */
