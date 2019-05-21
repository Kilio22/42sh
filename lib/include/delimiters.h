/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** tokens
*/

#ifndef TOKENS_H_
#define TOKENS_H_

enum delimiter_ids {
    ID_CMD = -1,
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
    ID_SQUOTES,
    ID_DQUOTES,
    ID_PARENTHESIS,
    ID_BACKTICKS,
    ID_NB
};

enum delimiter_types {
    T_WITHOUT,
    T_SEPARATOR,
    T_GET,
    T_CONTAINER,
    T_NB
};

typedef struct delimiter_s {
    char *delim;
    char *end;
    enum delimiter_ids id;
    enum delimiter_types type;
} delimiter_t;

extern const delimiter_t delim_tab[];

#endif /* !TOKENS_H_ */
