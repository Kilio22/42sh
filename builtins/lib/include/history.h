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
int init_history(struct breakpoints_s *historic);
int save_history(struct breakpoints_s *historic);
void free_history(struct breakpoints_s *historic);
int add_history(char *buff, struct breakpoints_s *historic);
char *find_history(struct breakpoints_s *historic, char *buff);
int replace_str_history(struct token_node *node, struct breakpoints_s *historic);


#endif /* !HISTORY_H_ */
