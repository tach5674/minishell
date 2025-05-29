/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built-in_execution.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikayel <mikayel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 20:02:04 by mikayel           #+#    #+#             */
/*   Updated: 2025/05/29 16:47:37 by mikayel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int  execute(t_cmd *cmd, t_shell *shell, int cmd_num)
{
    if (cmd_num == 0)
		return (0);
	else if (cmd_num == 1)
		return (ft_echo(cmd));
	else if (cmd_num == 2)
		return (ft_env(shell->env));
    else if (cmd_num == 3)
		return (ft_pwd());
    else if (cmd_num == 4)
        return (ft_exit(cmd, shell));
    else
        return (EXIT_FAILURE);
}

int    execute_builtin(t_cmd *cmd, t_shell *shell, int cmd_num, int extra_fd)
{
    int	old_stdout;
	int	old_stdin;
	int exit_code;
    
    if (cmd_num == 4 || cmd_num == 0)
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
    apply_redirections(cmd, extra_fd);
    exit_code = execute(cmd, shell, cmd_num);  
	dup2(old_stdout, STDOUT_FILENO);
	close(old_stdout);
	dup2(old_stdin, STDIN_FILENO);
	close(old_stdin);
    return (exit_code);
}

int	check_if_builtin(char *name)
{
	if (!name || ft_strcmp(name, ":") == 0)
		return (0);
	else if (ft_strcmp(name, "echo") == 0)
		return (1);
	else if (ft_strcmp(name, "env") == 0)
		return (2);
    else if (ft_strcmp(name, "pwd") == 0)
		return (3);
    else if (ft_strcmp(name, "exit") == 0)
        return (4);
	else 
    // else if (ft_strcmp(name, "export") == 0)
    // 	return (ft_export(cmd));
		return (-1);
}
