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

struct content_s {
    int number;
    time_t timer;
    char *command;
};

struct history_s {
    struct content_s *content;
    struct history_s *old;
    struct history_s *next;
};

struct breakpoints_s {
    struct history_s *head;
    struct history_s *last;
};

char *get_line(FILE *stream);
int init_history(struct breakpoints_s *historic);
int save_history(struct breakpoints_s *historic);
void free_history(struct breakpoints_s *historic);
int add_history(char *buff, struct breakpoints_s *historic);
char *find_history(struct breakpoints_s *historic, char *buff);
int replace_str_history(struct token_node *node,
struct breakpoints_s *historic);

#endif /* !HISTORY_H_ */
