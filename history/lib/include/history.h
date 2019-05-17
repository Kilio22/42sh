/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** history
*/

#include <time.h>

#ifndef HISTORY_H_
#define HISTORY_H_

typedef struct content_s {
    int number;
    struct tm hour;
    char *command;
} content_t;

typedef struct history_s {
    content_t *content;
    history_t *old;
    history_t *next;
} history_t;

#endif /* !HISTORY_H_ */
