/*
** EPITECH PROJECT, 2019
** my_str_to_word_array.c
** File description:
** Goes from a char * to char **, splitting every blanks
*/

#include <stdlib.h>
#include "my_string.h"

static int is_split_char(char const c)
{
    if (c == '\0')
        return (1);
    if (c == ' ')
        return (1);
    if (c == '\t')
        return (1);
    if (c == ':')
        return (1);
    if (c == '=')
        return (1);
    return (0);
}

static int skip_blanks(const char *str, int i)
{
    while (str[i] != '\0' && is_split_char(str[i]) == 1)
        i++;
    return (i);
}

static int my_count_nb_in_string(char const *str)
{
    int nb_count = 0;
    int len = my_strlen(str);

    for (int i = skip_blanks(str, 0); i < len; i = skip_blanks(str, i)) {
        if (str[i] != '\0')
            nb_count++;
        while (is_split_char(str[i]) == 0)
            i++;
    }
    return (nb_count);
}

char **my_str_to_path_array(char const *str)
{
    int word_count = my_count_nb_in_string(str);
    char **array = malloc(sizeof(char *) * (word_count + 1));
    int pos1 = skip_blanks(str, 0);
    int pos2 = pos1;
    int nbers_copied = 0;

    if (array == NULL)
        return (NULL);
    while (nbers_copied < word_count) {
        while (is_split_char(str[pos1]) == 0)
            pos1++;
        array[nbers_copied] = my_strndup(&str[pos2], (pos1 - pos2));
        if (array[nbers_copied] == NULL)
            return (NULL);
        pos1 = skip_blanks(str, pos1);
        pos2 = pos1++;
        nbers_copied++;
    }
    array[nbers_copied] = 0;
    return (array);
}
