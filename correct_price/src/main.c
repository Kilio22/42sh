/*
** EPITECH PROJECT, 2018
** main.c
** File description:
** Main function
*/

#include <time.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "my_string.h"
#include "my_stdio.h"
#include "my.h"
#include "correct_price.h"

int print_start(const char *score, const char *name, int fd, game_t *game)
{
    char *hscore;
    int highscore = -1;

    if (score != NULL)
        highscore = 0;
    hscore = get_next_line(fd);
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
    return 0;
}

int start_game(game_t *game)
{
    int fd = open("highscore.txt", O_RDONLY);
    char *score = NULL;
    char *name = my_strdup("personne");

    if (fd == -1)
        score = my_strdup("0");
    else {
        free(name);
        name = get_next_line(fd);
        if (name == NULL)
            return -1;
    }
    if (print_start(score, name, fd, game) == -1)
        return -1;
    free(name);
    free(score);
    close(fd);
    return 0;
}

int get_name(game_t *correct_price)
{
    char *buff;

    my_printf("\nQuel est votre nom ?\n\n");
    correct_price->name = get_next_line(0);
    if (correct_price->name == NULL)
        return -1;
    my_printf("\nEt bien bonne chance, %s !\nEcrivez ready pour commencer\n",
correct_price->name);
    while (1) {
        buff = get_next_line(0);
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

void manage_price_diff(game_t *correct_price, int price)
{
    if (price < 0 || price > 99999) {
        my_printf("Argument invalide.\n");
        return;
    }
    if (price < correct_price->number)
        my_printf("C'est PLUS !!!\n");
    else
        my_printf("C'est MOINS !!!\n");
}

int loop_game(game_t *correct_price)
{
    char *buff;
    int price;

    while (1) {
        buff = get_next_line(0);
        if (buff == NULL)
            return -1;
        if (my_str_isnum(buff, 0) == false) {
            my_printf("Argument invalide.\n");
            free(buff);
            continue;
        }
        price = my_atoi(buff);
        if (price == correct_price->number) {
            free(buff);
            return 0;
        }
        manage_price_diff(correct_price, price);
        free(buff);
    }
    return 0;
}

void save_new_highscore(game_t *correct_price)
{
    (void) correct_price;
    return;
}

void end_game(game_t *correct_price)
{
    correct_price->find = time(NULL) - correct_price->start;
    my_printf("\nET C'EST GA GNÉ !!!\n");
    my_printf("\nAvec un temps incroyable de %d secondes.\n",
correct_price->find);
    if (correct_price->find < correct_price->highscore ||
correct_price->highscore == 0) {
        my_printf("C'EST UN NOUVEAU RECORD ! BRAVO !!!\n");
        save_new_highscore(correct_price);
    } else
        my_printf("Dommage, ce score est inférieur au record.\n");
    my_printf("Merci d'avoir jouer, et à très bientôt pour un\
 nouveau Juste Prix :D\n\n");
}

int main(void)
{
    game_t correct_price;

    srand(time(0));
    if (system("clear") == -1)
        return 84;
    if (start_game(&correct_price) == -1)
        return 84;
    if (get_name(&correct_price) == -1)
        return 84;
    if (loop_game(&correct_price) == -1)
        return 84;
    end_game(&correct_price);
    free(correct_price.name);
    return (0);
}
