/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_execution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikayel <mikayel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 19:00:10 by mikayel           #+#    #+#             */
/*   Updated: 2025/06/02 12:00:58 by mikayel          ###   ########.fr       */
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

int	execute_in_child(t_cmd *cmd, t_shell *shell, bool wait, int extra_fd)
{
	char	*cmd_path;
	pid_t		pid;
	int		status;
	
	cmd_path = take_correct_path(cmd->name, ht_get(shell->env, "PATH"));
	pid = fork();
	if (pid == -1)
	{
		perror(shell->shell_name);
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		setup_signals_child();
		if (apply_redirections(cmd, extra_fd) != 0)
			exit(EXIT_FAILURE);
		execve(cmd_path, cmd->args, shell->shell_envp);
		free(cmd_path);
		ft_putstr_fd("Command not found\n", 2);
		free_shell(shell);
		exit(127);
	}
	free(cmd_path);
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