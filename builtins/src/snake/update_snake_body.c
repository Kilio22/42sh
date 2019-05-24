/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** update_snake_body
*/

#include <stdlib.h>
#include "snake.h"

static void update_last(game_t *snake)
{
    int x = snake->last[0];
    int y = snake->last[1];
    int i = 0;

    while (snake->body[i].direction != -1)
        i++;
    i--;
    snake->map[y][x] = 1;
    snake->last[0] = snake->body[i].x;
    snake->last[1] = snake->body[i].y;
}

static void update_new(game_t *snake, int new_x, int new_y)
{
    if (snake->map[new_y][new_x] == 3)
        snake->loose = true;
    if (snake->map[new_y][new_x] == 5 || snake->map[new_y][new_x] == 6) {
        snake->score = (snake->map[new_y][new_x] == 5) ?
snake->score + 1 : snake->score + 2;
        snake->highscore = (snake->score > snake->highscore) ?
snake->score : snake->highscore;
        generate_new_fruit(snake, new_x, new_y);
        generate_new_block(snake);
    }
    snake->map[snake->first[1]][snake->first[0]] = 3;
    snake->map[new_y][new_x] = 4;
    snake->first[0] = new_x;
    snake->first[1] = new_y;
}

static void update_body(game_t *snake, int new_x, int new_y)
{
    int i = 0;

    while (snake->body[i].direction != -1)
        i++;
    i--;
    for (; i > 0; i--) {
        snake->body[i].direction = snake->body[i - 1].direction;
        snake->body[i].x = snake->body[i - 1].x;
        snake->body[i].y = snake->body[i - 1].y;
    }
    snake->body[0].direction = snake->direction;
    snake->body[0].x = new_x;
    snake->body[0].y = new_y;
}

void update_snake(game_t *snake)
{
    int new_x = snake->first[0];
    int new_y = snake->first[1];

    if (snake->direction == UP)
        new_y--;
    if (snake->direction == LEFT)
        new_x--;
    if (snake->direction == DOWN)
        new_y++;
    if (snake->direction == RIGHT)
        new_x++;
    if (new_x < START_MAP_X || new_x > END_MAP_X
|| new_y < START_MAP_Y || new_y > END_MAP_Y) {
        snake->loose = true;
        return;
    }
    update_body(snake, new_x, new_y);
    update_last(snake);
    update_new(snake, new_x, new_y);
}