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
        my_printf("%d\t", current->content->number);
        if (timer->tm_hour < 10)
            my_putchar('0');
        my_printf("%d:", timer->tm_hour);
        if (timer->tm_min < 10)
            my_putchar('0');
        my_printf("%d\t%s\n", timer->tm_min, current->content->command);
        current = current->next;
    }
}

int main(void)
{
    struct token_node *node = malloc(sizeof(struct token_node));
    breakpoints_t *historic = malloc(sizeof(breakpoints_t));

    if (historic == NULL)
        return 84;
    if (node == NULL)
        return 84;
    node->content = my_strdup("!l -l | !c");
    if (init_history(historic) == -1)
        return 84;
    printf("ALLO %s\n", node->content);
    if (replace_str_history(node, historic) == -1)
        return 84;
    printf("ALHUILE %s\n", node->content);
    free(node->content);
    free(node);
    free_history(historic);
    free(historic);
    return 0;
}