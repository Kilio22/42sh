/*
** EPITECH PROJECT, 2019
** PSU_minishell2_2018
** File description:
** get_prompt
*/

#include <stddef.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "my.h"
#include "my_stdio.h"
#include "my_string.h"
#include "minishell.h"
#include "tokenizer.h"

char *get_dirname(void)
{
    char current[256];
    char *dirname = getcwd(current, sizeof(current));
    size_t i = strlen(dirname + 4);

    for (; dirname[i] != '/'; i--);
    return (strdup(dirname + i + 1));
}

char *read_prompt(void)
{
    char *line;

    if (isatty(0))
        my_printf("[Ouish@localhost%s]> ", get_dirname());
    line = get_next_line(0);
    if (!line)
        return (NULL);
    return line;
}

char **get_prompt(my_env_t *env)
{
    char *line_prompt = read_prompt();
    char **prompt;

    if (!line_prompt) {
        exit_shell(free_em(1, line_prompt), env);
        free_env(env);
        exit(0);
    }
    if (!*line_prompt) {
        free(line_prompt);
        return get_prompt(env);
    }
    struct token_node *nodelist = create_token_list_from_line(line_prompt);
    if (!nodelist)
        exit(84);
    while (nodelist) {
        printf("{%s}\t%d\n", nodelist->content, nodelist->id);
        nodelist = nodelist->next;
    }
    exit(0);
    prompt = my_str_towordarray(line_prompt, ";");
    free(line_prompt);
    if (!prompt)
        exit(84);
    return prompt;
}
