/*
** EPITECH PROJECT, 2018
** main.c
** File description:
** Main function
*/

#include <ncurses.h>
#include <unistd.h>
#include "snake.h"

static int read_input(game_t *snake)
{
    int ret_val = 0;
    char buff[20];

    if (read(0, buff, 20) != 0) {
        ret_val = check_event(buff, snake);
        for (int i = 0; i < 20; i++)
            buff[i] = '\0';
    }
    return ret_val;
}

static int window_loop(game_t *snake)
{
    int ret_val = 0;

    if (init_window() == 1)
        return close_window(1);
    while (1) {
        check_size_window();
        clear();
        ret_val = read_input(snake);
        if (ret_val == 1 || snake->loose == true)
            break;
        if (snake->pause == true)
            continue;
        update_snake(snake);
        if (snake->loose == true)
            break;
        if (print_map(snake) == 1)
            return close_window(1);
        refresh();
    }
    return close_window(0);
}

int snake(struct my_shell *shell __attribute__((unused)),
char **av __attribute__((unused)))
{
    int ret_val;

    game_t snake = init_game();
    ret_val = window_loop(&snake);
    save_snake(&snake);
    return (ret_val == 1) ? -1 : 0;
}
