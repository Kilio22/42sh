/*
** EPITECH PROJECT, 2019
** PSU_minishell1_2018
** File description:
** str_valid
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "my.h"

int is_alphanumeric(char c)
{
    if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
        return (1);
    if (c >= '0' && c <= '9')
        return (1);
    else
        return (0);
}

int is_alphanum(char *str)
{
    int count = 0;

    while (str[count] != '\0') {
        if (is_alphanumeric(str[count]) == 0 && str[count] != '_')
            return (0);
        count++;
    }
    return (1);
}

int is_alpha(char c)
{
    if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
        return (1);
    else
        return (0);
}

int my_str_isalpha(char *str)
{
    size_t count = 0;

    while (str[count] != '\0') {
        if (!is_alpha(str[count]))
            return 0;
        count++;
    }
    return 1;
}