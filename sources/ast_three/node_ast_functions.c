/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_ast_functions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikayel <mikayel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 14:30:34 by ggevorgi          #+#    #+#             */
/*   Updated: 2025/05/27 12:21:24 by mikayel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast *new_ast_node(t_ast_node_type type)
{
    t_ast *node;

    node = safe_malloc(sizeof(t_ast));
    if (node == NULL)
        return NULL;
    node->type = type;
    node->cmd = NULL;
    node->left = NULL;
    node->right = NULL;
    node->subshell = NULL;

    return (node);
}

t_cmd *new_cmd_node(char *name)
{
    t_cmd *cmd;

    cmd = malloc(sizeof(t_cmd));
    if (cmd == NULL)
        return (NULL);
    cmd->name = ft_strdup(name);
    cmd->args = malloc(sizeof(char *));
    if (cmd->args == NULL)
        return (NULL);
    cmd->args[0] = NULL;
    cmd->redirections = NULL;
    cmd->redir_count = 0;
    cmd->pipe_in = -1;
    cmd->pipe_out = -1;
    return (cmd);
}

void add_arg(t_cmd *cmd, char *arg)
{
    size_t i;
    char **new_args;

    i = 0;
    while (cmd->args[i] != NULL)
        i++;
    new_args = malloc(sizeof(char *) * (i + 2));
    if (new_args == NULL)
        return;

    i = 0;
    while (cmd->args[i] != NULL)
    {
        new_args[i] = cmd->args[i];
        i++;
    }
    new_args[i] = strdup(arg);
    new_args[i + 1] = NULL;
    free(cmd->args);
    cmd->args = new_args;
}

void add_redirection(t_cmd *cmd, t_redir_type type, char *target)
{
    t_redirection *redir;
    t_redirection **new_array;
    size_t i;

    redir = malloc(sizeof(t_redirection));
    if (redir == NULL)
        return ;
    redir->type = type;
    redir->target = ft_strdup(target);
    new_array = malloc(sizeof(t_redirection *) * (cmd->redir_count + 1));
    if (new_array == NULL)
        return;
    i = 0;
    while (i < cmd->redir_count)
    {
        new_array[i] = cmd->redirections[i];
        i++;
    }
    new_array[i] = redir;
    free(cmd->redirections);
    cmd->redirections = new_array;
    cmd->redir_count++;
}


t_redirection *new_redirection(t_redir_type type, char *target)
{
    t_redirection *redir;

    redir = malloc(sizeof(t_redirection));
    if (redir == NULL)
        return NULL;
    redir->type = type;
    redir->target = ft_strdup(target);
    return (redir);
}
