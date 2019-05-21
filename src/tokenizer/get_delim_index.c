/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** get_delim_index
*/

#include <string.h>
#include "delimiters.h"

size_t get_delim_index(char *ptr)
{
    size_t i = 0;

    while (delim_tab[i].str) {
        if (!strncmp(ptr, delim_tab[i].str, strlen(delim_tab[i].str)))
            break;
        ++i;
    }
    return i;
}
