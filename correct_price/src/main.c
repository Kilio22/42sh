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
    int fd = open("highscore.txt", O_CREAT | O_RDWR | O_TRUNC,
S_IRUSR | S_IWUSR);
    char *highscore = my_itoa(correct_price->find);

    if (fd == -1)
        return;
    if (highscore == NULL)
        return;
    write(fd, correct_price->name, my_strlen(correct_price->name));
    write(fd, "\n", 1);
    write(fd, highscore, my_strlen(highscore));
    free(highscore);
    close(fd);
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
    my_printf("Merci d'avoir jouer, et à très bientôt pour ");
    my_printf("un nouveau Juste Prix :D\n\n");
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
