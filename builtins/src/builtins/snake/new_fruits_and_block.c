/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** new_fruits_and_block
*/

#include <stdlib.h>
#include "snake.h"

static void add_last(game_t *snake)
{
    int i = 0;

    while (snake->body[i].direction != -1)
        i++;
    i--;
    snake->last[0] = snake->body[i].x;
    snake->last[1] = snake->body[i].y;
}

void generate_new_block(game_t *snake)
{
    int i = 0;
    int x;
    int y;

    while (snake->body[i].direction != -1)
        i++;
    snake->body[i].direction = snake->body[i - 1].direction;
    x = snake->body[i - 1].x;
    y = snake->body[i - 1].y;
    if (snake->body[i - 1].direction == UP)
        y++;
    if (snake->body[i - 1].direction == DOWN)
        y--;
    if (snake->body[i - 1].direction == RIGHT)
        x--;
    if (snake->body[i - 1].direction == LEFT)
        x++;
    snake->body[i].x = x;
    snake->body[i].y = y;
    snake->map[y][x] = 3;
    add_last(snake);
}

void generate_new_fruit(game_t *snake, int new_x, int new_y)
{
    int ret_val = 1;
    int x;
    int y;
    int color = rand() % 10;

    while (ret_val != 0) {
        x = START_MAP_X + (rand() % 40);
        y = START_MAP_Y + (rand() % 20);
        if (x == new_x && y == new_y)
            continue;
        if (snake->map[y][x] == 3 || snake->map[y][x] == 4)
            continue;
        ret_val = 0;
        snake->map[y][x] = (color < 3) ? 6 : 5;
    }
}