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

typedef struct content_s {
    int number;
    time_t timer;
    char *command;
} content_t;

typedef struct history_s {
    content_t *content;
    struct history_s *old;
    struct history_s *next;
} history_t;

typedef struct breakpoints_s {
    history_t *head;
    history_t *last;
} breakpoints_t;

struct token_node {
    char *content;
};

char *get_line(FILE *stream);
int init_history(breakpoints_t *historic);
int save_history(breakpoints_t *historic);
void free_history(breakpoints_t *historic);
void print_history(breakpoints_t *historic);
int add_history(char *buff, breakpoints_t *historic);
char *find_history(breakpoints_t *historic, char *buff);
int replace_str_history(struct token_node *node, breakpoints_t *historic);


#endif /* !HISTORY_H_ */
