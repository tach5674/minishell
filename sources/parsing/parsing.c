/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggevorgi <sp1tak.gg@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 13:29:01 by ggevorgi          #+#    #+#             */
/*   Updated: 2025/06/03 10:36:53 by ggevorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast	*parse_pipeline(t_token **tokens, t_shell *shell)
{
	t_ast	*left;
	t_ast	*node;

	left = parse_command_or_subshell(tokens, shell);
	if (!left)
		return (NULL);
	while (*tokens && (*tokens)->type == TOKEN_PIPE)
	{
		if (!left)
		{
			syntax_error("|");
			return (NULL);
		}
		*tokens = (*tokens)->next;
		node = new_ast_node(AST_PIPE);
		node->left = left;
		node->right = parse_command_or_subshell(tokens, shell);
		if (!node->right)
		{
			syntax_error("newline");
			return (free_ast(node), NULL);
		}
		left = node;
	}
	return (left);
}

t_ast	*parse_command_or_subshell(t_token **tokens, t_shell *shell)
{
	t_ast	*node;

	if (!*tokens)
		return (NULL);
	if ((*tokens)->type == TOKEN_PAREN_LEFT)
		return (parse_subshell(tokens, shell));
	node = new_ast_node(AST_COMMAND);
	node->cmd = create_cmd_from_tokens(*tokens, shell);
	if (!node->cmd)
		return (free(node), NULL);
	while (*tokens && (*tokens)->type != TOKEN_PIPE
		&& (*tokens)->type != TOKEN_AND && (*tokens)->type != TOKEN_OR
		&& (*tokens)->type != TOKEN_PAREN_RIGHT)
		*tokens = (*tokens)->next;
	return (node);
}

t_ast	*parse_and_or(t_token **tokens, t_shell *shell)
{
	t_ast			*left;
	t_ast			*node;
	t_ast_node_type	type;

	left = parse_pipeline(tokens, shell);
	if (!left)
		return (NULL);
	while (*tokens && ((*tokens)->type == TOKEN_AND
			|| (*tokens)->type == TOKEN_OR))
	{
		if ((*tokens)->type == TOKEN_AND)
			type = AST_AND;
		else
			type = AST_OR;
		*tokens = (*tokens)->next;
		node = new_ast_node(type);
		node->left = left;
		node->right = parse_pipeline(tokens, shell);
		if (!node->right)
			return (free_ast(node), syntax_error("newline"), NULL);
		left = node;
	}
	return (left);
}

t_ast	*parse_subshell(t_token **tokens, t_shell *shell)
{
	t_ast	*subshell_node;
	t_ast	*child;

	if (*tokens && (*tokens)->type == TOKEN_PAREN_LEFT)
	{
		*tokens = (*tokens)->next;
		child = parse_and_or(tokens, shell);
		if (!child)
			return (NULL);
		if (*tokens && (*tokens)->type == TOKEN_PAREN_RIGHT)
			*tokens = (*tokens)->next;
		else
		{
			syntax_error("expected ')'");
			free_ast(child);
			return (NULL);
		}
		subshell_node = new_ast_node(AST_SUBSHELL);
		subshell_node->cmd = new_cmd_node(NULL, shell);
		subshell_node->left = child;
		return (subshell_node);
	}
	return (NULL);
}

t_ast	*parse(t_token **tokens, t_shell *shell)
{
	t_ast	*ast;

	ast = parse_and_or(tokens, shell);
	if (ast && *tokens)
	{
		syntax_error("unexpected token");
		free_ast(ast);
		return (NULL);
	}
	return (ast);
}
