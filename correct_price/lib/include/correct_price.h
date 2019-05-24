/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** correct_price
*/

#ifndef CORRECT_PRICE_H_
#define CORRECT_PRICE_H_

typedef struct game_s {
    char *name;
    int number;
    int highscore;
    time_t start;
    time_t find;
} game_t;

int get_name(game_t *correct_price);
int start_game(game_t *game);
char *get_line(FILE *stream);
int correct_price(struct my_shell *shell __attribute__((unused)),
char **av __attribute__((unused)));

#endif /* !CORRECT_PRICE_H_ */
