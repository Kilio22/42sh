/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** start_game
*/

#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdbool.h>
#include "my.h"
#include "my_string.h"
#include "my_stdio.h"
#include "correct_price.h"

static int print_start(const char *score, const char *name,
FILE *stream, game_t *game)
{
    char *hscore;
    int highscore = -1;

    if (score != NULL)
        highscore = 0;
    hscore = get_line(stream);
    if (hscore == NULL)
        highscore = 0;
    else if (my_str_isnum(hscore, 0) == false)
        highscore = 0;
    highscore = (highscore == 0) ? highscore : my_atoi(hscore);
    my_printf("\nBonjour et bienvenue dans un nouveau Juste Prix !!!\n");
    my_printf("Le prix est compris entre 0 et 99999 euros.\n");
    my_printf("Le record est actuellement de %d secondes, détenu par %s\n",
highscore, name);
    game->highscore = highscore;
    free(hscore);
    return 0;
}

int start_game(game_t *game)
{
    FILE *stream = fopen("highscore.txt", "r");
    char *score = NULL;
    char *name = my_strdup("personne");

    if (stream == NULL)
        score = my_strdup("0");
    else {
        free(name);
        name = get_line(stream);
        if (name == NULL)
            return -1;
    }
    if (print_start(score, name, stream, game) == -1)
        return -1;
    free(name);
    free(score);
    fclose(stream);
    return 0;
}

int get_name(game_t *correct_price)
{
    char *buff;

    my_printf("\nQuel est votre nom ?\n\n");
    correct_price->name = get_line(stdin);
    if (correct_price->name == NULL)
        return -1;
    my_printf("\nEt bien bonne chance, %s !\nEcrivez ready pour commencer\n",
correct_price->name);
    while (1) {
        buff = get_line(stdin);
        if (my_strcmp(buff, "ready") == 0)
            break;
        my_printf("\nArgument invalide. Ecrivez ready pour commencer\n");
        free(buff);
    }
    free(buff);
    correct_price->start = time(NULL);
    correct_price->number = rand() % 100000;
    return 0;
}