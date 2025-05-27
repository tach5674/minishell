/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikayel <mikayel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 12:41:01 by mikayel           #+#    #+#             */
/*   Updated: 2025/05/27 13:21:57 by mikayel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redirect_files(t_redirection *redir)
{
	int	fd;
	
	if (redir->type == REDIR_IN)
	{
		fd = open(redir->target, O_RDONLY);
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	else if (redir->type == REDIR_OUT)
	{
		fd = open(redir->target, O_WRONLY | O_CREAT | O_TRUNC, 0666);
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	else if (redir->type == REDIR_APPEND)
	{
		fd = open(redir->target, O_WRONLY | O_CREAT | O_APPEND, 0666);
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
}

void	apply_redirections(t_cmd *cmd, int extra_fd)
{
	size_t	i;
	
	if (cmd->pipe_out != -1)
	{
		dup2(cmd->pipe_out, STDOUT_FILENO);
		close(cmd->pipe_out);
	}
	if (cmd->pipe_in != -1)
	{
		dup2(cmd->pipe_in, STDIN_FILENO);
		close(cmd->pipe_in);
	}
	if (extra_fd != -1)
		close(extra_fd);
	i = 0;
	while (i < cmd->redir_count)
	{
		redirect_files(cmd->redirections[i]);
		i++;	
	}
}

void	set_pipe_redirections(t_ast *ast, int fd, t_redir_type type)
{	
	if (ast->type == AST_COMMAND)
	{
		if (type == REDIR_IN)
			ast->cmd->pipe_in = fd;
		else
			ast->cmd->pipe_out = fd;
	}
	else if (ast->type == AST_AND || ast->type == AST_OR)
	{
		set_pipe_redirections(ast->left, fd, type);
		set_pipe_redirections(ast->right, fd, type);		
	}
	else if (ast->type == AST_SUBSHELL)
		set_pipe_redirections(ast->left, fd, type);
	else if (ast->type == AST_PIPE)
		set_pipe_redirections(ast->right, fd, type);
}
