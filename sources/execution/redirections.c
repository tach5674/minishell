/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggevorgi <sp1tak.gg@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 12:41:01 by mikayel           #+#    #+#             */
/*   Updated: 2025/06/02 12:18:04 by mikayel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int    return_error(char *name)
{
    char    *msg;
    
    msg = ft_strjoin("minishell: ", name);
    perror(msg);
    free(msg);
	return (EXIT_FAILURE);
}

int	open_dup_fd(t_redirection *redir, int redir_fd, int flags, mode_t mode)
{
	int	fd;
	
	if (!redir->target)
	{
		signal_status = 130;
		exit(130);
	}
	fd = open(redir->target, flags, mode);
	if (fd == -1)	
		exit_error(redir->target);
	if (redir->type == REDIR_HEREDOC)		
		if (unlink(redir->target) == -1)
			exit_error(redir->target);
	if (dup2(fd, redir_fd) == -1)
		exit_error(redir->target);
	if (close(fd) == -1)
		exit_error(redir->target);
}

int	redirect_files(t_redirection *redir)
{
	if (redir->type == REDIR_IN)
		return (open_dup_fd(redir, STDIN_FILENO, O_RDONLY, 0));
	else if (redir->type == REDIR_OUT)
		return (open_dup_fd(redir, STDOUT_FILENO, 
			O_WRONLY | O_CREAT | O_TRUNC, 0666));
	else if (redir->type == REDIR_APPEND)
		return (open_dup_fd(redir, STDOUT_FILENO, 
			O_WRONLY | O_CREAT | O_APPEND, 0666));
	else if (redir->type == REDIR_HEREDOC)
		return (open_dup_fd(redir, STDIN_FILENO, O_RDONLY, 0));
	else
		return (-1);
}

int	apply_redirections(t_cmd *cmd, int extra_fd)
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
		if (redirect_files(cmd->redirections[i]) == -1)
			return (return_error(cmd->redirections[i]->target));
		i++;	
	}
	return (0);
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
	{
		if (type == REDIR_IN)
			ast->cmd->pipe_in = fd;
		else
			ast->cmd->pipe_out = fd;
		set_pipe_redirections(ast->left, fd, type);
	}
	else if (ast->type == AST_PIPE)
		set_pipe_redirections(ast->right, fd, type);
}
