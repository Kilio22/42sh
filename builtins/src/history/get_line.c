/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** get_line
*/

#include <stdlib.h>
#include <stdio.h>
#include "my_string.h"
#include "my.h"

char *get_line(FILE *stream)
{
    size_t nb_char = 0;
    char *buff = NULL;

    if (getline(&buff, &nb_char, stream) == -1)
        return free(buff), NULL;
    if (buff[my_strlen(buff) - 1] == '\n')
        buff[my_strlen(buff) - 1] = '\0';
    return buff;
}