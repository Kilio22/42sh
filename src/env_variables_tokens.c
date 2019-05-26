/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** env_variables_tokens
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "my.h"
#include "shell.h"

static char *strcat_for_env_variables(char *str, char *new, char *ptr)
{
    char *full_str = NULL;
    size_t total_len = 0;
    size_t tmp_len = 0;

    for (; ptr[tmp_len] && is_alphanumeric(ptr[tmp_len])
&& ptr[tmp_len] != '_'; tmp_len++);
    total_len = strlen(str) - tmp_len + strlen(new);
    full_str = malloc(sizeof(char) * (total_len + 1));
    if (!full_str)
        exit(84);
    for (total_len = 0; str[total_len] != '$'; total_len++);
    full_str[0] = '\0';
    strncpy(full_str, str, total_len);
    full_str[total_len] = '\0';
    strcat(full_str, new);
    strcat(full_str, &str[total_len + tmp_len + 1]);
    return full_str;
}

static char *get_var(struct my_shell *shell, char *name)
{
    char *var;

    if (!name)
        return NULL;
    var = my_get(shell, name);
    if (!var)
        var = my_getenv(shell, name);
    return var;
}

static int env_variables(struct token_node *token, struct my_shell *shell)
{
    char *ptr = NULL;
    char *var = NULL;
    size_t len = 0;

    if (!token->content || (ptr = strchr(token->content, '$')) == NULL)
        return -1;
    ptr++;
    for (; ptr[len] && is_alphanumeric(ptr[len]) && ptr[len] != '_'; len++);
    if (!(ptr = strndup(ptr, len)))
        return -1;
    var = get_var(shell, ptr);
    if (!var) {
        ptr[len] = '\0';
        fprintf(stderr, "%s: Undefined variable.\n", ptr);
        return -1;
    }
    var = strcat_for_env_variables(token->content, var, ptr);
    free(token->content);
    token->content = var;
    return 0;
}

static int get_return_value(struct token_node *token, struct my_shell *shell)
{
    char *return_val = my_itoa(shell->n_return);

    if (!return_val)
        return -1;
    free(token->content);
    token->content = return_val;
    return 0;
}

int env_variables_token(struct token_node *token, struct my_shell *shell)
{
    int n_val = 0;

    if (!strncmp(token->content, "$?", 2))
        n_val = get_return_value(token, shell);
    else if (strchr(token->content, '$') && token->content[1] != '\0')
        n_val = env_variables(token, shell);
    return n_val;
}