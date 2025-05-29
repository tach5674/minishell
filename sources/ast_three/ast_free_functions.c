/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_free_functions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikayel <mikayel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 13:36:34 by ggevorgi          #+#    #+#             */
/*   Updated: 2025/05/29 17:53:29 by mikayel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_redirections(t_redirection **redirs, size_t count)
{
	size_t	i;

	if (!redirs)
		return;
	i = 0;
	while (i < count)
	{
		if (redirs[i])
		{
			free(redirs[i]->target);
			free(redirs[i]);
		}
		i++;
	}
	free(redirs);
}

void	free_cmd(t_cmd *cmd)
{
	size_t	i;

	if (!cmd)
		return;
	free(cmd->name);
	if (cmd->args)
	{
		i = 0;
		while (cmd->args[i])
			free(cmd->args[i++]);
		free(cmd->args);
	}
	free_redirections(cmd->redirections, cmd->redir_count);
	free(cmd);
}

void	free_ast(t_ast *ast)
{
	if (!ast)
		return;
	if (ast->type == AST_COMMAND)
		free_cmd(ast->cmd);
	else if (ast->type == AST_PIPE || ast->type == AST_AND || ast->type == AST_OR)
	{
		free_ast(ast->left);
		free_ast(ast->right);
	}
	else if (ast->type == AST_SUBSHELL)
	{
		free_cmd(ast->cmd);
		free_ast(ast->left);
	}
	free(ast);
}
