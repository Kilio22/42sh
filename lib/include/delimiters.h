/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** tokens
*/

#ifndef TOKENS_H_
#define TOKENS_H_

#include <sys/types.h>

enum delim_ids {
    ID_SPACE,
    ID_TAB,
    ID_SEPARATOR,
    ID_OR,
    ID_AND,
    ID_PIPE,
    ID_NOWAIT,
    ID_DB_FULL_RREDIRECTION,
    ID_DB_RREDIRECTION,
    ID_FULL_RREDIRECTION,
    ID_RREDIRECTION,
    ID_DB_LREDIRECTION,
    ID_LREDIRECTION,
    ID_BACKTICKS,
    ID_SQUOTES,
    ID_DQUOTES,
    ID_PARENTHESIS,
    ID_BACKSLASH,
    ID_TEXT,
    ID_NB
};

enum delim_types {
    T_WITHOUT,
    T_SEPARATOR,
    T_GET,
    T_CONTAINER,
    T_INHIBITOR,
    T_NB
};

typedef struct delimiter_s {
    char *str;
    char *end;
    enum delim_ids id;
    enum delim_types type;
} delimiter_t;

/* Delimiter array */
extern const delimiter_t delim_tab[];

/* Useful functions */
size_t get_delim_index(char *ptr);

#define DELIM_STR(i) (delim_tab[i].str)
#define DELIM_END(i) (delim_tab[i].end)
#define DELIM_ID(i) (delim_tab[i].id)
#define DELIM_TYPE(i) (delim_tab[i].type)

#endif /* !TOKENS_H_ */
