/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggevorgi <sp1tak.gg@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 11:22:50 by mikayel           #+#    #+#             */
/*   Updated: 2025/06/03 10:20:52 by ggevorgi         ###   ########.fr       */
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

static int	execute_subshell(t_ast *ast, t_shell *shell, bool wait, int extra_fd)
{
	pid_t	pid;
	int		status;
	int		exit_code;
	
	pid = fork();
	if (pid == -1)
	{
		perror(shell->shell_name);
		exit(EXIT_FAILURE);
	}
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

static int	execute_pipe(t_ast *ast, t_shell *shell, bool last_pipe)
{
	int		pipefd[2];
	int		exit_code;
	int		extra_fd;
	int 	status;
	
	if (ast->left->type == AST_PIPE)
		extra_fd = execute_pipe(ast->left, shell, false);
	else
		extra_fd = -1;
	if (pipe(pipefd) == -1)
	{
		perror(shell->shell_name);
		exit(EXIT_FAILURE);
	}
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
	{
		exit_code = execute_ast(ast->right, shell, last_pipe, -1);
		close(pipefd[0]);
		while (wait(&status) != -1)
			;
		return (exit_code);
	}
	return (pipefd[0]);
}

int	execute_ast(t_ast *ast, t_shell *shell, bool wait, int extra_fd)
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
		if (execute_ast(ast->left, shell, wait, extra_fd) != 0)
			return (execute_ast(ast->right, shell, wait, extra_fd));
		return (0);
	}
	else if (ast->type == AST_SUBSHELL)
		return (execute_subshell(ast, shell, wait, extra_fd));
	else if (ast->type == AST_PIPE)
		return (execute_pipe(ast, shell, true));
	return (0);
}

void execute_commands(t_shell *shell)
{
    t_token *tokens;
    t_token *tokens_tmp;

    tokens = tokenize(shell->commands, 0);
    free(shell->commands);
    tokens_tmp = tokens;

    if (syntax_error_check(tokens))
    {
        free_tokens(tokens_tmp);
        return;
    }

    shell->ast = parse(&tokens, shell);
    free_tokens(tokens_tmp);

    if (shell->ast == NULL)
        return;

    setup_signals_parent_exec();
    shell->last_status_code = execute_ast(shell->ast, shell, true, -1);

    if (signal_status == SIGINT)
        write(1, "\n", 1);
    else if (signal_status == SIGQUIT)
        write(1, "Quit (core dumped)\n", 19);
    signal_status = 0;
    setup_signals();

    free_ast(shell->ast);
    shell->ast = NULL;
}
