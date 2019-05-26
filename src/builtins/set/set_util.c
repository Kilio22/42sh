/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** set_util
*/

#include <unistd.h>
#include <string.h>

char *get_val(char *arg)
{
    char *ptr = NULL;

    if (!arg)
        return NULL;
    ptr = strchr(arg, '=');
    if (!ptr)
        return strdup("");
    ptr[0] = '\0';
    ptr++;
    return strdup(ptr);
}