/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikayel <mikayel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 11:22:50 by mikayel           #+#    #+#             */
/*   Updated: 2025/05/27 13:39:30 by mikayel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_operator_syntax_err(t_token *tokens)
{
	bool	is_operator;

	is_operator = false;
	if (tokens->type != TOKEN_WORD && tokens->type != TOKEN_PAREN_LEFT)
	{
		syntax_error(tokens->value);
		return (true);
	}
	while (tokens)
	{
		if (tokens->type != TOKEN_WORD)
		{
			if (is_operator)
			{
				syntax_error(tokens->value);
				return (true);
			}
			is_operator = true;
		}
		else
			is_operator = false;
		tokens = tokens->next;
	}
	return (false);
}

void	free_split(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

static char	*take_correct_path(char *command, char *path)
{
	char	**paths;
	int		i;
	char	*tmp;
	char	*tmp2;

	i = -1;
	if (access(command, X_OK) == 0)
		return (ft_strdup(command));
	paths = ft_split(path, ':');
	if (!paths)
		return (NULL);
	while (paths[++i] != NULL)
	{
		tmp = ft_strjoin(paths[i], "/");
		tmp2 = ft_strjoin(tmp, command);
		free(tmp);
		if (access(tmp2, F_OK) != -1)
		{
			free_split(paths);
			return (tmp2);
		}
		free(tmp2);
	}
	free_split(paths);
	return (NULL);
}

static int	execute_cmd(t_cmd *cmd, t_shell *shell_data, bool wait, int extra_fd)
{
	char	*cmd_path;
	pid_t		pid;
	int		status;
	
	cmd_path = take_correct_path(cmd->name, ht_get(shell_data->env, "PATH"));
	pid = fork();
	if (pid == -1)
	{
		perror(shell_data->shell_name);
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		apply_redirections(cmd, extra_fd);
		execve(cmd_path, cmd->args, shell_data->shell_envp);
		free(cmd_path);
		exit(EXIT_FAILURE);
	}
	free(cmd_path);
	if (wait == true)
	{
		waitpid(pid, &status, 0);
		return (status);
	}
	// printf("%s\n", cmd->name);
	return (0);
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
	return (status);
}

static int	execute_pipe(t_ast *ast, t_shell *shell_data, bool last_pipe)
{
	int	pipefd[2];
	int	exit_code;
	int	extra_fd;
	
	// int	old_stdout;
	// int	old_stdin;

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
	// old_stdout = dup(STDOUT_FILENO);
	// old_stdin = dup(STDIN_FILENO);
	
	// dup2(pipefd[1], STDOUT_FILENO);
	// close(pipefd[1]);
	if (ast->left->type == AST_PIPE)
		execute_ast(ast->left->right, shell_data, false, pipefd[0]);
	else
		execute_ast(ast->left, shell_data, false, pipefd[0]);
	close(pipefd[1]);
	if (extra_fd != -1)
		close(extra_fd);
	// dup2(old_stdout, STDOUT_FILENO);
	// close(old_stdout);
	
	// dup2(pipefd[0], STDIN_FILENO);
	// close(pipefd[0]);
	
	if (last_pipe == true)
	{
		exit_code = execute_ast(ast->right, shell_data, last_pipe, -1);
		close(pipefd[0]);
		while (wait(NULL) != -1)
			;
		return (exit_code);
	}
	// dup2(old_stdin, STDIN_FILENO);
	// close(old_stdin);
	return (pipefd[0]);
}

int	execute_ast(t_ast *ast, t_shell *shell_data, bool wait, int extra_fd)
{
	int	exit_code;

	if (ast)
	{
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
	}
	printf("AST is empty\n");
	return (0);
}

void	execute_commands(t_shell *shell_data)
{
	t_ast *ast;
	t_token *tokens;
	t_token *tokens_tmp;

	tokens = tokenize(shell_data->commands, 0);
	tokens_tmp = tokens;
	if (!is_operator_syntax_err(tokens))
	{
		ast = parse(&tokens);
		if (ast != NULL)
		{
			// print_ast(ast);
			execute_ast(ast, shell_data, true, -1);
		}
		free_ast(ast);
	}
	free_tokens(tokens_tmp);
}