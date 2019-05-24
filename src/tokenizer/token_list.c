/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** token_list
*/

#include <stddef.h>
#include "delimiters.h"

const delimiter_t delim_tab[] = {
    {" ", "", ID_SPACE, T_WITHOUT},
    {"\t", "", ID_TAB, T_WITHOUT},
    {";", "", ID_SEPARATOR, T_SEPARATOR},
    {"||", "", ID_OR, T_SEPARATOR},
    {"&&", "", ID_AND, T_SEPARATOR},
    {"|", "", ID_PIPE, T_GET},
    {"&", "", ID_NOWAIT, T_GET},
    {">>&", "", ID_DB_FULL_RREDIRECTION, T_GET},
    {">>", "", ID_DB_RREDIRECTION, T_GET},
    {">&", "", ID_FULL_RREDIRECTION, T_GET},
    {">", "", ID_RREDIRECTION, T_GET},
    {"<<", "", ID_DB_LREDIRECTION, T_GET},
    {"<", "", ID_LREDIRECTION, T_GET},
    {"`", "`", ID_BACKTICKS, T_CONTAINER},
    {"'", "'", ID_SQUOTES, T_CONTAINER},
    {"\"", "\"", ID_DQUOTES, T_CONTAINER},
    {"(", ")", ID_PARENTHESIS, T_CONTAINER},
    {"\\", "", ID_BACKSLASH, T_INHIBITOR},
    {NULL, NULL, ID_TEXT, T_WITHOUT}
};
