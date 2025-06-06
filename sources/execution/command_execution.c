/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_execution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikayel <mikayel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 19:00:10 by mikayel           #+#    #+#             */
/*   Updated: 2025/06/06 14:04:45 by mikayel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

bool	add_last_arg_env(char **args, t_shell *shell)
{
	int	i;

	i = 1;
	while (args[i])
		i++;
	if (ht_add(shell->env, "_", *args) == false)
	{
		perror("minishell");
		return (false);
	}
	return (true);
}

int	execute_in_child(t_cmd *cmd, t_shell *shell, bool wait, int extra_fd)
{
	char	*cmd_path;
	pid_t		pid;
	int		status;
	char	**envp;
	
	pid = fork();
	if (pid == -1)
	{
		perror(shell->shell_name);
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		setup_signals_child();
		if (add_last_arg_env(cmd->args, shell) == false)
		{
			free_shell(shell);
			exit(EXIT_FAILURE);
		}
		if (apply_redirections(cmd, extra_fd) != 0)
		{
			free_shell(shell);
			exit(EXIT_FAILURE);
		}
		cmd_path = get_path(cmd->name, shell);
		envp = ht_to_envp(shell->env);
		if (!envp && errno)
		{
			perror("minishell");
			free_shell(shell);
			free(cmd_path);
			exit(EXIT_FAILURE);
		}
		execve(cmd_path, cmd->args, envp);
		perror("minishell");
		free(cmd_path);
		free_shell(shell);
		exit(126);
	}
	if (wait == false)
		return (0);
	waitpid(pid, &status, 0);
	return (get_exit_code(status));
}

int	execute_cmd(t_cmd *cmd, t_shell *shell, bool wait, int extra_fd)
{
	int	cmd_num;
	int	pid;
	int	status;
	
	if (apply_expansions(cmd->args, shell) == false)
		return (EXIT_FAILURE);
	free(cmd->name);
	cmd->name = ft_strdup(cmd->args[0]);
	if (!cmd->name)
	{
		perror("minishell");
		return (EXIT_FAILURE);
	}
	cmd_num = check_if_builtin(cmd->name);
    if (cmd_num == -1)
		return (execute_in_child(cmd, shell, wait, extra_fd));
	if (cmd->pipe_in == -1 && cmd->pipe_out == -1)
		return (execute_builtin(cmd, shell, cmd_num, -1));
	pid = fork();
	if (pid == -1)
	{
		perror(cmd->name);
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		cmd->in_subshell = true;
		status = execute_builtin(cmd, shell, cmd_num, extra_fd);
		free_shell(shell);
		exit(status);
	}
	if (wait == false)
		return (0);
	waitpid(pid, &status, 0);
	return (get_exit_code(status));
}