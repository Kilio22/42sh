/*
** EPITECH PROJECT, 2018
** main.c
** File description:
** Main function
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdbool.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "history.h"
#include "my_stdio.h"
#include "my_string.h"
#include "my.h"

void print_history(breakpoints_t *historic)
{
    history_t *current = historic->head;
    struct tm *timer;

    while (current != NULL) {
        timer = localtime(&(current->content->timer));
        if (timer == NULL)
            continue;
        my_printf("%d\t%d:", current->content->number,
timer->tm_hour, timer->tm_min, current->content->command);
        if (timer->tm_min < 10)
            my_putchar('0');
        my_printf("%d\t%s\n", timer->tm_min, current->content->command);
        current = current->next;
    }
}

char *my_ltoa(long int nb)
{
    char str[50] = {0};
    int isneg = (nb < 0) ? 1 : 0;
    int r;
    int i = 0;

    if (nb == -2147483648)
        return (my_strdup("-2147483648"));
    nb = (nb < 0) ? -nb : nb;
    do {
        r = nb % 10;
        nb /= 10;
        str[i++] = r + '0';
    } while (nb);
    if (isneg)
        str[i++] = '-';
    str[i] = '\0';
    return (my_strdup(my_revstr(str)));
}

int is_in_history(char *buff, breakpoints_t *historic)
{
    history_t *current = historic->head;

    while (current != NULL) {
        if (my_strcmp(buff, current->content->command) == 0)
            return 0;
        current = current->next;
    }
    return -1;
}

int change_history(char *buff, breakpoints_t *historic)
{
    history_t *head = historic->head;
    time_t timer = time(&timer);

    while (historic->head != NULL) {
        if (my_strcmp(buff, historic->head->content->command) == 0)
            break;
        historic->head = historic->head->next;
    }
    historic->head->content->timer = timer;
    historic->head->content->number = historic->last->content->number + 1;
    if (historic->head->old != NULL && historic->head->next != NULL)
        historic->head->old->next = historic->head->next;
    if (historic->head->next != NULL && historic->head->old != NULL)
        historic->head->next->old = historic->head->old;
    if (historic->head->next != NULL)
        historic->last->next = historic->head;
    historic->head->old = historic->last;
    historic->head->next = NULL;
    historic->last = historic->head;
    historic->head = head;
    return 0;
}

int add_history(char *buff, breakpoints_t *historic)
{
    history_t *new_historic;

    if (is_in_history(buff, historic) == 0)
        return change_history(buff, historic);
    new_historic = malloc(sizeof(history_t));
    if (new_historic == NULL)
        return -1;
    new_historic->content = malloc(sizeof(content_t));
    if (new_historic->content == NULL)
        return -1;
    if (time(&(new_historic->content->timer)) == -1)
        return -1;
    new_historic->content->command = my_strdup(buff);
    if (new_historic->content->command == NULL)
        return -1;
    new_historic->content->number = historic->last->content->number + 1;
    historic->last->next = new_historic;
    new_historic->next = NULL;
    new_historic->old = historic->last;
    historic->last = new_historic;
    return 0;
}

char *command_number(breakpoints_t *historic, int number)
{
    history_t *current = historic->head;

    while (current->content->number != number)
        current = current->next;
    return my_strdup(current->content->command);
}

char *command_str(breakpoints_t *historic, char *str)
{
    history_t *current = historic->head;

    while (current != NULL && my_strncmp(current->content->command,
str, my_strlen(str)) != 0)
        current = current->next;
    if (current == NULL)
        return NULL;
    return my_strdup(current->content->command);
}

char *find_history(breakpoints_t *historic, char *buff)
{
    int number;
    char *str = my_strdup(buff + 1);
    char *ret_str;

    if (my_strlen(buff) < 2)
        return NULL;
    if (my_str_isnum(str, false) == true) {
        number = my_atoi(str);
        free(str);
        if (number > historic->last->content->number) {
            fprintf(stderr, "!%d: Event not found\n", number);
            return NULL;
        }
        return command_number(historic, number);
    }
    ret_str = command_str(historic, str);
    free(str);
    return ret_str;
}

int history(breakpoints_t *historic)
{
    char *buff;
    char *str;

    while (1) {
        buff = get_line(stdin);
        if (buff == NULL)
            continue;
        if (my_strcmp("quit", buff) == 0)
            break;
        if (my_strncmp("!", buff, 1) == 0) {
            str = find_history(historic, buff);
            if (str != NULL) {
                fprintf(stderr, "%s\n", str);
                free(str);
            }
            free(buff);
            continue;
        }
        if (add_history(buff, historic) == -1)
            return -1;
        if (my_strcmp("history", buff) == 0)
            print_history(historic);
        free(buff);
    }
    free(buff);
    return 0;
}

void fill_content(breakpoints_t *historic, history_t *content, char *time,
char *str)
{
    static int number = 1;
    time_t timer;

    if (my_str_isnum(time, false) == false)
        return;
    timer = strtol(time, NULL, 10);
    content->content->number = number;
    content->content->timer = timer;
    content->content->command = my_strdup(str);
    content->next = NULL;
    content->old = historic->last;
    if (historic->last != NULL)
        historic->last->next = content;
    historic->last = content;
    if (historic->head == NULL)
        historic->head = content;
    number++;
}

int read_history(breakpoints_t *historic, FILE *stream)
{
    char *time = get_line(stream);
    char *str = get_line(stream);
    history_t *content;

    while (time != NULL && str != NULL) {
        content = malloc(sizeof(history_t));
        if (content == NULL)
            return -1;
        content->content = malloc(sizeof(content_t));
        if (content->content == NULL)
            return -1;
        fill_content(historic, content, time, str);
        free(time);
        free(str);
        time = get_line(stream);
        str = get_line(stream);
    }
    return 0;
}

int empty_history(breakpoints_t *historic)
{
    history_t *content = malloc(sizeof(history_t));
    time_t timer;

    if (content == NULL)
        return -1;
    content->next = NULL;
    content->old = NULL;
    content->content = malloc(sizeof(content_t));
    if (content->content == NULL)
        return -1;
    content->content->command = my_strdup("./42sh");
    if (content->content->command == NULL)
        return -1;
    content->content->number = 0;
    content->content->timer = time(&timer);
    historic->head = content;
    historic->last = content;
    return 0;
}

int init_history(breakpoints_t *historic)
{
    FILE *stream = fopen(".history", "r");
    time_t timer = time(&timer);
    int ret_val = 0;

    historic->head = NULL;
    historic->last = NULL;
    if (stream == NULL) {
        ret_val = empty_history(historic);
        return ret_val;
    } else {
        ret_val = read_history(historic, stream);
        if (historic->head == NULL)
            ret_val = empty_history(historic);
    }
    fclose(stream);
    return ret_val;
}

void free_history(breakpoints_t *historic)
{
    history_t *next = historic->head->next;

    while (historic->head != NULL) {
        free(historic->head->content->command);
        free(historic->head->content);
        free(historic->head);
        historic->head = next;
        if (next != NULL)
            next = historic->head->next;
    }
}

int save_history(breakpoints_t *historic)
{
    int fd = open(".history", O_CREAT | O_RDWR | O_TRUNC,
S_IRUSR | S_IWUSR);
    char *time;
    history_t *current = historic->head;

    while (current != NULL) {
        time = my_ltoa(current->content->timer);
        if (write(fd, time, my_strlen(time)) == -1)
            return -1;
        if (write(fd, "\n", 1) == -1)
            return -1;
        if (write(fd, current->content->command,
my_strlen(current->content->command)) == -1)
            return -1;
        if (write(fd, "\n", 1) == -1)
            return -1;
        current = current->next;
        free(time);
    }
    close(fd);
    return 0;
}

int main(void)
{
    int ret_val = 0;
    breakpoints_t *historic = malloc(sizeof(breakpoints_t));

    if (historic == NULL)
        return 84;
    if (init_history(historic) == -1)
        return 84;
    if (history(historic) == -1)
        ret_val = 84;
    if (save_history(historic) == -1)
        ret_val = 84;
    free_history(historic);
    free(historic);
    return ret_val;
}
