/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikayel <mikayel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 13:33:29 by mikayel           #+#    #+#             */
/*   Updated: 2025/05/27 13:35:05 by mikayel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_ast_node(t_ast *node, int depth)
{
	if (!node)
		return ;
	// Отступы для визуальной структуры дерева
	for (int i = 0; i < depth; i++)
		printf("  ");
	// Печать типа узла
	if (node->type == AST_COMMAND)
	{
		printf("AST_COMMAND\n");
		printf("%*sCommand: %s\n", depth * 2, "", node->cmd->name);
		for (size_t i = 0; i < node->cmd->redir_count; i++)
		{
			printf("%*sRedirection %zu: %s %s\n", depth * 2, "", i + 1,
				node->cmd->redirections[i]->type == REDIR_IN ? "<" : node->cmd->redirections[i]->type == REDIR_OUT ? ">" : node->cmd->redirections[i]->type == REDIR_APPEND ? ">>" : "<<",
				node->cmd->redirections[i]->target);
		}
	}
	else if (node->type == AST_PIPE)
	{
		printf("AST_PIPE\n");
	}
	else if (node->type == AST_AND)
	{
		printf("AST_AND\n");
	}
	else if (node->type == AST_OR)
	{
		printf("AST_OR\n");
	}
	else if (node->type == AST_SUBSHELL)
	{
		printf("AST_SUBSHELL\n");
	}
	// Рекурсивный вызов для левого и правого поддеревьев
	if (node->left)
		print_ast_node(node->left, depth + 1);
	if (node->right)
		print_ast_node(node->right, depth + 1);
	if (node->subshell)
		print_ast_node(node->subshell, depth + 1);
}

void	print_ast(t_ast *ast)
{
	if (!ast)
	{
		printf("AST is NULL\n");
		return ;
	}
	print_ast_node(ast, 0);
}

const char	*token_type_str(t_token_type type)
{
	switch (type)
	{
	case TOKEN_WORD:
		return ("WORD");
	case TOKEN_PIPE:
		return ("PIPE");
	case TOKEN_AND:
		return ("AND");
	case TOKEN_OR:
		return ("OR");
	case TOKEN_REDIR_IN:
		return ("REDIR_IN");
	case TOKEN_REDIR_OUT:
		return ("REDIR_OUT");
	case TOKEN_REDIR_APPEND:
		return ("APPEND");
	case TOKEN_HEREDOC:
		return ("HEREDOC");
	case TOKEN_PAREN_LEFT:
		return ("PAREN_LEFT");
	case TOKEN_PAREN_RIGHT:
		return ("PAREN_RIGHT");
	case TOKEN_EOF:
		return ("EOF");
	default:
		return ("UNKNOWN");
	}
}

void	print_tokens(t_token *list)
{
	while (list)
	{
		printf("Type: %-12s | Value: '%s'\n", token_type_str(list->type),
			list->value);
		list = list->next;
	}
}