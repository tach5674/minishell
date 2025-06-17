/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_execution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzohraby <mzohraby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 14:54:37 by ggevorgi          #+#    #+#             */
/*   Updated: 2025/06/17 16:24:58 by mzohraby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	add_last_arg_env(char **args, t_shell *shell)
{
	int	i;

	if (!args || !(*args))
	{
		ht_unset(shell->env, "_");
		return (true);
	}
	i = 0;
	while (args[i])
		i++;
	if (ht_add(shell->env, "_", args[i - 1]) == false)
	{
		perror("minishell");
		return (false);
	}
	return (true);
}

static int	execute_in_child(t_cmd *cmd, t_shell *shell, bool wait,
		int extra_fd)
{
	char	*cmd_path;
	pid_t	pid;
	int		status;
	char	**envp;

	pid = fork();
	if (pid == -1)
		return (handle_error(cmd->args[0]));
	if (pid == 0)
	{
		setup_signals_child();
		if (apply_redirections(cmd, extra_fd) == EXIT_FAILURE)
			exit_error(shell, NULL, EXIT_FAILURE);
		cmd_path = get_path(cmd->args[0], shell);
		envp = ht_to_envp(shell->env, false, 0, 0);
		if (!envp)
			exit_error(shell, cmd_path, EXIT_FAILURE);
		execve(cmd_path, cmd->args, envp);
		perror("minishell");
		exit_error(shell, cmd_path, 126);
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

	if (apply_expansions(cmd, shell) == false)
		return (EXIT_FAILURE);
	if (add_last_arg_env(cmd->args, shell) == false)
		return (EXIT_FAILURE);
	cmd_num = check_if_builtin(cmd->args[0]);
	if (cmd_num == -1)
		return (execute_in_child(cmd, shell, wait, extra_fd));
	if (cmd->pipe_in == -1 && cmd->pipe_out == -1)
		return (execute_builtin(cmd, shell, cmd_num, -1));
	pid = fork();
	if (pid == -1)
		return (handle_error(cmd->args[0]));
	if (pid == 0)
	{
		cmd->in_subshell = true;
		status = execute_builtin(cmd, shell, cmd_num, extra_fd);
		exit_error(shell, NULL, status);
	}
	if (wait == false)
		return (0);
	return (waitpid(pid, &status, 0), get_exit_code(status));
}
