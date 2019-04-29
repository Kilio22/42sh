/*
** EPITECH PROJECT, 2019
** PSU_minishell2_2018
** File description:
** my_split_array
*/

#include <stdlib.h>
#include <stdio.h>
#include "my.h"
#include "my_string.h"

char **my_cut_array(char ***src, size_t index)
{
    size_t len = my_strarraylen(*src);
    char **new_array = malloc(sizeof(char *) * (index + 1));
    char **new_src = malloc(sizeof(char *) * (len - index));

    if (!new_array || !new_src)
        return NULL;
    for (size_t i = 0; i < index; i++)
        new_array[i] = (*src)[i];
    for (size_t i = index + 1; i < len; i++) {
        new_src[i - index - 1] = (*src)[i];
    }
    new_array[index] = NULL;
    new_src[len - index - 1] = NULL;
    free((*src)[index]);
    free(*src);
    *src = new_src;
    return new_array;
}
