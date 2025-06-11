/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_execution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikayel <mikayel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 19:00:10 by mikayel           #+#    #+#             */
/*   Updated: 2025/06/11 17:55:44 by mikayel          ###   ########.fr       */
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

int	execute_in_child(t_cmd *cmd, t_shell *shell, bool wait, int extra_fd)
{
	char	*cmd_path;
	pid_t		pid;
	int		status;
	char	**envp;
	
	pid = fork();
	if (pid == -1)
	{
		perror("minishell");
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
		if (apply_redirections(cmd, extra_fd) == -1)
		{
			free_shell(shell);
			exit(EXIT_FAILURE);
		}
		cmd_path = get_path(cmd->args[0], shell);
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
	
	if (apply_expansions(cmd, shell) == false)
		return (EXIT_FAILURE);
	// free(cmd->args[0]);
	// if (!cmd->args || !cmd->args[0])
	// {
	// 	int tmp_stdout = dup(STDOUT_FILENO);
	// 	int tmp_stdin = dup(STDIN_FILENO);
	// 	int tmp_stderr = dup(STDERR_FILENO);
	
	// 	if (apply_redirections(cmd, -1) == -1)
	// 	{
	// 		dup2(tmp_stdout, STDOUT_FILENO);
	// 		dup2(tmp_stdin, STDIN_FILENO);
	// 		dup2(tmp_stderr, STDERR_FILENO);
	// 		close(tmp_stdout);
	// 		close(tmp_stdin);
	// 		close(tmp_stderr);
	// 		return (EXIT_FAILURE);
	// 	}
	
	// 	// Выполнять нечего — просто закрыть файлы и восстановить std*
	// 	dup2(tmp_stdout, STDOUT_FILENO);
	// 	dup2(tmp_stdin, STDIN_FILENO);
	// 	dup2(tmp_stderr, STDERR_FILENO);
	// 	close(tmp_stdout);
	// 	close(tmp_stdin);
	// 	close(tmp_stderr);
	
	// 	return (EXIT_SUCCESS);
	// }
	// cmd->args[0] = ft_strdup(cmd->args[0]);
	// if (errno && !cmd->args[0])
	// {
	// 	perror("minishell");
	// 	return (EXIT_FAILURE);
	// }
	cmd_num = check_if_builtin(cmd->args[0]);
    if (cmd_num == -1)
		return (execute_in_child(cmd, shell, wait, extra_fd));
	if (cmd->pipe_in == -1 && cmd->pipe_out == -1)
		return (execute_builtin(cmd, shell, cmd_num, -1));
	pid = fork();
	if (pid == -1)
	{
		perror(cmd->args[0]);
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