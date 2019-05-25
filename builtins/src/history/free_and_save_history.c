/*
** EPITECH PROJECT, 2019
** history
** File description:
** free_and_save_history
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include "builtins.h"
#include "history.h"
#include "my_string.h"
#include "my.h"

static char *my_ltoa(long int nb)
{
    char str[50] = {0};
    int isneg = (nb < 0) ? 1 : 0;
    int r;
    int i = 0;

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

void free_history(struct breakpoints_s *historic)
{
    struct history_s *next = historic->head->next;

    while (historic->head != NULL) {
        free(historic->head->content->command);
        free(historic->head->content);
        free(historic->head);
        historic->head = next;
        if (next != NULL)
            next = historic->head->next;
    }
}

int save_history(struct breakpoints_s *historic)
{
    int fd = open(".history", O_CREAT | O_RDWR | O_TRUNC,
S_IRUSR | S_IWUSR);
    char *time;
    struct history_s *current = historic->head;

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