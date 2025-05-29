/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikayel <mikayel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 11:22:50 by mikayel           #+#    #+#             */
/*   Updated: 2025/05/29 01:27:53 by mikayel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		get_exit_code(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	else
		return (EXIT_FAILURE);
}

static int	execute_subshell(t_ast *ast, t_shell *shell_data, bool wait, int extra_fd)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
	{
		perror(shell_data->shell_name);
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		if (extra_fd != -1)
			close(extra_fd);
		exit(execute_ast(ast, shell_data, true, -1));
	}
	if (wait == false)
		return (0);
	waitpid(pid, &status, 0);
	return (get_exit_code(status));
}

static int	execute_pipe(t_ast *ast, t_shell *shell_data, bool last_pipe)
{
	int		pipefd[2];
	int		exit_code;
	int		extra_fd;
	int 	status;
	
	if (ast->left->type == AST_PIPE)
		extra_fd = execute_pipe(ast->left, shell_data, false);
	else
		extra_fd = -1;
	if (pipe(pipefd) == -1)
	{
		perror(shell_data->shell_name);
		exit(EXIT_FAILURE);
	}
	set_pipe_redirections(ast->left, pipefd[1], REDIR_OUT);
	set_pipe_redirections(ast->right, pipefd[0], REDIR_IN);
	if (ast->left->type == AST_PIPE)
		execute_ast(ast->left->right, shell_data, false, pipefd[0]);
	else
		execute_ast(ast->left, shell_data, false, pipefd[0]);
	close(pipefd[1]);
	if (extra_fd != -1)
		close(extra_fd);
	if (last_pipe == true)
	{
		exit_code = execute_ast(ast->right, shell_data, last_pipe, -1);
		close(pipefd[0]);
		while (wait(&status) != -1)
			;
		return (exit_code);
	}
	return (pipefd[0]);
}

int	execute_ast(t_ast *ast, t_shell *shell_data, bool wait, int extra_fd)
{
	int	exit_code;

	if (ast->type == AST_COMMAND)
		return (execute_cmd(ast->cmd, shell_data, wait, extra_fd));
	else if (ast->type == AST_AND)
	{
		exit_code = execute_ast(ast->left, shell_data, wait, extra_fd);
		if (exit_code == 0)
			return (execute_ast(ast->right, shell_data, wait, extra_fd));
		return (exit_code);
	}
	else if (ast->type == AST_OR)
	{
		if (execute_ast(ast->left, shell_data, wait, extra_fd) != 0)
			return (execute_ast(ast->right, shell_data, wait, extra_fd));
		return (0);
	}
	else if (ast->type == AST_SUBSHELL)
		return (execute_subshell(ast->left, shell_data, wait, extra_fd));
	else if (ast->type == AST_PIPE)
		return (execute_pipe(ast, shell_data, true));
	return (0);
}

void	execute_commands(t_shell *shell_data)
{
	t_ast *ast;
	t_token *tokens;
	t_token *tokens_tmp;

	tokens = tokenize(shell_data->commands, 0);
	tokens_tmp = tokens;
	if (!syntax_error_check(tokens))
	{
		ast = parse(&tokens);
		free_tokens(tokens_tmp);
		if (ast != NULL)
		{
			// print_ast(ast);
			setup_signals_parent_exec();
			shell_data->last_status_code = execute_ast(ast, shell_data, true, -1);
			// printf("%d\n", shell_data->last_status_code);
			if (signal_status == SIGINT)
				write(1, "\n", 1);
			else if (signal_status == SIGQUIT)
				write(1, "Quit (core dumped)\n", 19);
			signal_status = 0;
			setup_signals();
			free_ast(ast);
		}
	}
}