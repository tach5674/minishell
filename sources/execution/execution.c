/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzohraby <mzohraby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 11:22:50 by mikayel           #+#    #+#             */
/*   Updated: 2025/05/25 14:56:03 by mzohraby         ###   ########.fr       */
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

static int	execute_cmd(t_cmd *cmd, t_shell *shell_data, bool wait)
{
	char	*cmd_path;
	int		pid;
	int		status;
	
	cmd_path = take_correct_path(cmd->name, ht_get(shell_data->env, "PATH"));
	pid = fork();
	if (pid == 0)
	{
		if (cmd->pipe_out != -1)
			dup2(cmd->pipe_out, STDOUT_FILENO);
		if (cmd->pipe_in != -1)
			dup2(cmd->pipe_in, STDIN_FILENO);
		execve(cmd_path, cmd->args, shell_data->shell_envp);
	}
	if (wait == true)
	{
		waitpid(pid, &status, 0);
		return (status);
	}
	// printf("%s\n", cmd->name);
	return (0);
}

static int	execute_subshell(t_ast *ast, t_shell *shell_data, bool wait)
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
		exit(execute_ast(ast, shell_data, true));
	if (wait == false)
		return (0);
	waitpid(pid, &status, 0);
	return (status);
}

static void	set_pipe_redirections(t_ast *ast, int fd, t_redir_type type)
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

static int	execute_pipe(t_ast *ast, t_shell *shell_data, bool last_pipe)
{
	int	pipefd[2];
	int	exit_code;
	// int	old_stdout;
	// int	old_stdin;

	if (ast->left->type = AST_PIPE)
		execute_pipe(ast->left, shell_data, false);
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
	
	execute_ast(ast->left, shell_data, false);
	close(pipefd[1]);
	// dup2(old_stdout, STDOUT_FILENO);
	// close(old_stdout);
	
	// dup2(pipefd[0], STDIN_FILENO);
	// close(pipefd[0]);
	
	if (last_pipe == true)
	{
		exit_code = execute_ast(ast->right, shell_data, last_pipe);
		while (wait(NULL) != -1)
			;
		return (exit_code);
	}
	
	// dup2(old_stdin, STDIN_FILENO);
	// close(old_stdin);
	return (0);
}

int	execute_ast(t_ast *ast, t_shell *shell_data, bool wait)
{
	int	exit_code;

	if (ast)
	{
		if (ast->type == AST_COMMAND)
			return (execute_cmd(ast->cmd, shell_data, wait));
		else if (ast->type == AST_AND)
		{
			exit_code = execute_ast(ast->left, shell_data, wait);
			if (exit_code == 0)
				return (execute_ast(ast->right, shell_data, wait));
			return (exit_code);
		}
		else if (ast->type == AST_OR)
		{
			if (execute_ast(ast->left, shell_data, wait) != 0)
				return (execute_ast(ast->right, shell_data, wait));
			return (0);
		}
		else if (ast->type == AST_SUBSHELL)
		{
			return (execute_subshell(ast->left, shell_data, wait));
		}
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
			print_ast(ast);
			execute_ast(ast, shell_data, true);
		}
		free_ast(ast);
	}
	free_tokens(tokens_tmp);
}