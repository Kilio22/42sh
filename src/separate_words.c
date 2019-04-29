/*
** EPITECH PROJECT, 2019
** PSU_minishell2_2018
** File description:
** separate_words
*/

#include <stdbool.h>
#include "my.h"
#include "my_string.h"
#include "minishell.h"

static char *add_spaces(char *line, int i, bool is_double)
{
    if (is_double) {
        if (i && line[i - 1] != line[i] && line[i - 1] != ' ')
            line = my_str_addchar(line, ' ', i++);
        if (line[i + 1] && line[i + 1] != line[i] && line[i + 1] != ' ')
            line = my_str_addchar(line, ' ', i + 1);
        if (i && line[i + 1] && line[i] == line[i - 1] && line[i + 1] != ' ')
            line = my_str_addchar(line, ' ', i + 1);
    } else {
        if (i && line[i - 1] != ' ')
            line = my_str_addchar(line, ' ', i++);
        if (line[i + 1] && line[i + 1] != ' ')
            line = my_str_addchar(line, ' ', i + 1);
    }
    return line;
}

char *separate_words(char *line)
{
    char *ptr;

    for (size_t i = 0; line[i]; i++) {
        ptr = my_strchr((char *) CHAR_WORDS, line[i]);
        if (ptr)
            line = add_spaces(line, i, (ptr - CHAR_WORDS < 4) ? 1 : 0);
    }
    return line;
}
