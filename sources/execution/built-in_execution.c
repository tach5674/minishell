/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built-in_execution.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikayel <mikayel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 14:54:28 by ggevorgi          #+#    #+#             */
/*   Updated: 2025/06/13 21:34:54 by mikayel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	execute(t_cmd *cmd, t_shell *shell, int cmd_num)
{
	if (cmd_num == 0)
		return (0);
	else if (cmd_num == 1)
		return (ft_echo(cmd));
	else if (cmd_num == 2)
		return (ft_env(cmd, shell->env));
	else if (cmd_num == 3)
		return (ft_pwd(cmd, shell->env));
	else if (cmd_num == 4)
		return (ft_exit(cmd, shell));
	else if (cmd_num == 5)
		return (ft_cd(cmd, shell->env));
	else if (cmd_num == 6)
		return (ft_export(cmd, shell->env));
	else if (cmd_num == 7)
		return (ft_unset(cmd, shell->env));
	else
		return (EXIT_FAILURE);
}

int	execute_builtin(t_cmd *cmd, t_shell *shell, int cmd_num, int extra_fd)
{
	int	old_stdout;
	int	old_stdin;
	int	exit_code;

	if (cmd_num == 4)
	{
		if (cmd->pipe_out != -1)
			close(cmd->pipe_out);
		if (cmd->pipe_in != -1)
			close(cmd->pipe_in);
		if (extra_fd != -1)
			close(extra_fd);
		return (execute(cmd, shell, cmd_num));
	}
	old_stdout = dup(STDOUT_FILENO);
	old_stdin = dup(STDIN_FILENO);
	if (apply_redirections(cmd, extra_fd) != 0)
		exit_code = EXIT_FAILURE;
	else
		exit_code = execute(cmd, shell, cmd_num);
	dup2(old_stdout, STDOUT_FILENO);
	dup2(old_stdin, STDIN_FILENO);
	return (close(old_stdout), close(old_stdin), exit_code);
}

int	check_if_builtin(char *name)
{
	if (!name|| ft_strcmp(name, ":") == 0)
		return (0);
	else if (ft_strcmp(name, "echo") == 0)
		return (1);
	else if (ft_strcmp(name, "env") == 0)
		return (2);
	else if (ft_strcmp(name, "pwd") == 0)
		return (3);
	else if (ft_strcmp(name, "exit") == 0)
		return (4);
	else if (ft_strcmp(name, "cd") == 0)
		return (5);
	else if (ft_strcmp(name, "export") == 0)
		return (6);
	else if (ft_strcmp(name, "unset") == 0)
		return (7);
	else
		return (-1);
}
