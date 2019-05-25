/*
** EPITECH PROJECT, 2019
** PSU_minishell2_2018
** File description:
** get_prompt
*/

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "my.h"
#include "my_stdio.h"
#include "my_string.h"
#include "parser.h"

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

void print_pipe(struct pipe_s *cmd)
{
    printf("----LES PIPES----\n");
    while (cmd) {
        printf("\\\\\\\\\\CHANGEMENT DE PIPE\\\\\\\\\\\n");
        while (cmd->token_list) {
        printf("ID = %d\n", cmd->token_list->id);
        printf("CONTENT = %s\n", cmd->token_list->content);
            cmd->token_list = cmd->token_list->next;
        }
        printf("REDIRECTION\n");
        for (int i = 0; i < 6; i++)
            if (cmd->redirections[i])
                printf("%s\n", cmd->redirections[i]);
        cmd = cmd->next;
    }
}

void print_list(struct cmd_s *cmd)
{
    while (cmd) {
        printf("NEW LIST NODE WITH ID %d\n", cmd->id);
        print_pipe(cmd->pipe);
        printf("----SORTIE DES PIPES----\n");
        while (cmd->token_list) {
            printf("ID = %d\n", cmd->token_list->id);
            printf("CONTENT = %s\n", cmd->token_list->content);
            cmd->token_list = cmd->token_list->next;
        }
        cmd = cmd->next;
    }
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
    struct cmd_s *cmd = separate_token_list(nodelist);
    if (!cmd)
        exit(84);
    if (pipe_parser(cmd) == -1)
        exit(84);
    print_list(cmd);
    exit(0);
    prompt = my_str_towordarray(line_prompt, ";");
    free(line_prompt);
    if (!prompt)
        exit(84);
    return prompt;
}
