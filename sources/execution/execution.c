/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikayel <mikayel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 14:54:49 by ggevorgi          #+#    #+#             */
/*   Updated: 2025/06/13 20:29:24 by mikayel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	execute_ast(t_ast *ast, t_shell *shell, bool wait, int extra_fd);

static int	execute_subshell(t_ast *ast, t_shell *shell, bool wait,
		int extra_fd)
{
	pid_t	pid;
	int		status;
	int		exit_code;

	pid = fork();
	if (pid == -1)
		return (perror("minishell"), EXIT_FAILURE);
	if (pid == 0)
	{
		set_in_subshell(ast->left);
		exit_code = execute_ast(ast->left, shell, true, -1);
		if (extra_fd != -1)
			close(extra_fd);
		if (ast->cmd->pipe_in != -1)
			close(ast->cmd->pipe_in);
		if (ast->cmd->pipe_out != -1)
			close(ast->cmd->pipe_out);
		free_shell(shell);
		exit(exit_code);
	}
	if (wait == false)
		return (0);
	waitpid(pid, &status, 0);
	return (get_exit_code(status));
}

static int	execute_last_pipe(t_ast *ast, t_shell *shell, int pipefd,
		bool last_pipe)
{
	int	exit_code;
	int	status;

	exit_code = execute_ast(ast->right, shell, last_pipe, -1);
	close(pipefd);
	while (wait(&status) != -1)
		;
	return (exit_code);
}

static int	execute_pipe(t_ast *ast, t_shell *shell, bool last_pipe)
{
	int	pipefd[2];
	int	extra_fd;

	if (ast->left->type == AST_PIPE)
		extra_fd = execute_pipe(ast->left, shell, false);
	else
		extra_fd = -1;
	if (pipe(pipefd) == -1)
		return (perror("minishell"), EXIT_FAILURE);
	set_pipe_redirections(ast->left, pipefd[1], REDIR_OUT);
	set_pipe_redirections(ast->right, pipefd[0], REDIR_IN);
	if (ast->left->type == AST_PIPE)
		execute_ast(ast->left->right, shell, false, pipefd[0]);
	else
		execute_ast(ast->left, shell, false, pipefd[0]);
	close(pipefd[1]);
	if (extra_fd != -1)
		close(extra_fd);
	if (last_pipe == true)
		return (execute_last_pipe(ast, shell, pipefd[0], last_pipe));
	return (pipefd[0]);
}

static int	execute_ast(t_ast *ast, t_shell *shell, bool wait, int extra_fd)
{
	int	exit_code;

	if (ast->type == AST_COMMAND)
		return (execute_cmd(ast->cmd, shell, wait, extra_fd));
	else if (ast->type == AST_AND)
	{
		exit_code = execute_ast(ast->left, shell, wait, extra_fd);
		if (exit_code == 0)
			return (execute_ast(ast->right, shell, wait, extra_fd));
		return (exit_code);
	}
	else if (ast->type == AST_OR)
	{
		exit_code = execute_ast(ast->left, shell, wait, extra_fd);
		if (g_signal_status == SIGQUIT)
		{
			write(1, "Quit (core dumped)\n", 19);
			g_signal_status = 0;
		}
		if (exit_code != 0 && exit_code != 130)
			return (execute_ast(ast->right, shell, wait, extra_fd));
		return (0);
	}
	else if (ast->type == AST_SUBSHELL)
		return (execute_subshell(ast, shell, wait, extra_fd));
	else if (ast->type == AST_PIPE)
		return (execute_pipe(ast, shell, true));
	return (0);
}

void	execute_commands(t_shell *shell)
{
	t_token	*tokens;
	t_token	*tokens_tmp;
	int		exit_code;

	add_history(shell->commands);
	tokens = tokenize(shell->commands, 0);
	free(shell->commands);
	if (!tokens && errno)
		return ;
	tokens_tmp = tokens;
	if (syntax_error_check(tokens))
	{
		if (shell->last_status_code)
			free(shell->last_status_code);
		shell->last_status_code = ft_itoa(2);
		if (!shell->last_status_code)
			perror("minishell");		
		return (free_tokens(tokens_tmp));
	}
	shell->ast = parse(&tokens, shell);
	free_tokens(tokens_tmp);
	if (shell->ast == NULL)
		return ;
	setup_signals_parent_exec();
	exit_code = execute_ast(shell->ast, shell, true, -1);
	if (shell->last_status_code)
		free(shell->last_status_code);
	shell->last_status_code = ft_itoa(exit_code);
	if (!shell->last_status_code)
		perror("minishell");
	setup_signals();
}
