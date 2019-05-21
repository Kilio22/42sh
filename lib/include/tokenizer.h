/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** tokenizer
*/

#ifndef TOKENIZER_H_
#define TOKENIZER_H_

struct token_node {
    struct token_node *next;
    struct token_node *prev;
    char *content;
};

#endif /* !TOKENIZER_H_ */
