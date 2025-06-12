/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzohraby <mzohraby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 15:32:55 by mzohraby          #+#    #+#             */
/*   Updated: 2025/06/12 16:34:37 by mzohraby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_error(char *name)
{
	char	*msg;

	if (!name)
	{
		perror("minishell");
		return (EXIT_FAILURE);
	}
	msg = ft_strjoin("minishell: ", name);
	if (!msg)
	{
		perror("minishell");
		return (EXIT_FAILURE);
	}
	perror(msg);
	free(msg);
	return (EXIT_FAILURE);
}

void	exit_error(t_shell *shell, char *cmd_path, int exit_code)
{
	if (cmd_path)
		free(cmd_path);
	free_shell(shell);
	exit(exit_code);
}

int	get_exit_code(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
	{
		g_signal_status = WTERMSIG(status);
		return (128 + WTERMSIG(status));
	}
	else
		return (EXIT_FAILURE);
}

void	set_in_subshell(t_ast *ast)
{
	if (ast->type == AST_COMMAND)
		ast->cmd->in_subshell = true;
	else if (ast->type == AST_AND || ast->type == AST_OR)
	{
		set_in_subshell(ast->left);
		set_in_subshell(ast->right);
	}
	else if (ast->type == AST_PIPE)
	{
		set_in_subshell(ast->left);
		set_in_subshell(ast->right);
	}
}
