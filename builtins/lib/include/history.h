/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** history
*/

#include <stdio.h>
#include <time.h>

#ifndef HISTORY_H_
#define HISTORY_H_

struct token_node {
    char *content;
};

char *get_line(FILE *stream);
int init_history(breakpoints_t *historic);
int save_history(breakpoints_t *historic);
void free_history(breakpoints_t *historic);
int add_history(char *buff, breakpoints_t *historic);
char *find_history(breakpoints_t *historic, char *buff);
int replace_str_history(struct token_node *node, breakpoints_t *historic);


#endif /* !HISTORY_H_ */
