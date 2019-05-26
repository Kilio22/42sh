/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** apply_alias
*/

#include <string.h>
#include <stdlib.h>
#include "shell.h"
#include "my_string.h"
#include "my.h"

static void fix_nodes(struct token_node **node, struct token_node *new)
{
    struct token_node *head = new;

    new->prev = (*node)->prev;
    if ((*node)->prev != NULL)
        (*node)->prev->next = new;
    while (new->next != NULL)
        new = new->next;
    new->next = (*node)->next;
    if ((*node)->next != NULL)
        (*node)->next->prev = new;
    free((*node)->content);
    free(*node);
    *node = head;
}

static int new_node(struct token_node **node, char **command)
{
    struct token_node *new;

    if (strcmp(*command, (*node)->content) == 0) {
        free(*command);
        return 0;
    }
    new = create_token_list_from_line(*command);
    free(*command);
    if (new == NULL)
        return -1;
    fix_nodes(node, new);
    return 0;
}

int modify_string_alias(char **command, struct alias_s aliases[MAX_ALIAS],
int index, char ***touched)
{
    char **array = my_str_towordarray((*command), " ");

    if (array == NULL)
        return -1;
    if (is_in_touched(aliases[index].name, *touched) == true)
        return -2;
    *touched = my_realloc_array(*touched, strdup(aliases[index].name));
    *command = free_and_dup_command(command, index, aliases);
    if (*command == NULL)
        return -1;
    for (int i = 1; array[i] != NULL; i++) {
        *command = my_strcat_freeleft(*command, " ");
        if (*command == NULL)
            return -1;
        *command = my_strcat_freeleft(*command, array[i]);
        if (*command == NULL)
            return -1;
    }
    free_tab(array);
    return 0;
}

static int apply_alias(char **command, struct alias_s aliases[MAX_ALIAS],
char ***touched)
{
    int index;
    char **array = my_str_towordarray((*command), " ");
    int ret_val;

    if ((*command) == NULL || array == NULL)
        return -1;
    index = find_alias(aliases, array[0]);
    if (index == -1 || aliases[index].name == NULL) {
        free_tab(array);
        return -2;
    } else
        ret_val = modify_string_alias(command, aliases, index, touched);
    free_tab(array);
    return ret_val;
}

int loop_apply_alias(struct token_node **node,
struct alias_s aliases[MAX_ALIAS])
{
    int ret_val = 0;
    char *alias = NULL;
    char **touched = malloc(sizeof(char *));

    if ((*node)->content != NULL)
        alias = strdup((*node)->content);
    if (alias == NULL || touched == NULL)
        return -1;
    touched[0] = NULL;
    while (ret_val == 0) {
        ret_val = apply_alias(&alias, aliases, &touched);
        if (ret_val == -1)
            return -1;
        if (alias == NULL)
            return -1;
        if (ret_val == -2) {
            free_tab(touched);
            return new_node(node, &alias);
        }
    }
    return 0;
}