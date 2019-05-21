/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** get_delim_index
*/

#include <string.h>
#include "delimiters.h"

ssize_t get_delim_index(char *ptr)
{
    for (size_t i = 0; delim_tab[i].delim; i++) {
        if (!strncmp(delim_tab[i].delim, ptr, strlen(delim_tab[i].delim)))
            return i;
    }
    return ID_TEXT;
}
