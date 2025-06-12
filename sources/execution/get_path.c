/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzohraby <mzohraby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:37:02 by mikayel           #+#    #+#             */
/*   Updated: 2025/06/12 16:11:37 by mzohraby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_access(char *name, t_shell *shell)
{
	struct stat	statbuf;

	if (access(name, F_OK) == -1)
	{
		handle_error(name);
		free_shell(shell);
		exit(127);
	}
	if (access(name, X_OK) == -1)
	{
		handle_error(name);
		free_shell(shell);
		exit(126);
	}
	if (stat(name, &statbuf) == 0 && S_ISDIR(statbuf.st_mode))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(name, 2);
		ft_putstr_fd(": is a directory\n", 2);
		free_shell(shell);
		exit(126);
	}
}

char	*take_correct_path(char *command, char *path, t_shell *shell)
{
	char	**paths;
	int		i;
	char	*tmp;

	i = -1;
	if (access(command, X_OK) == 0)
		return (ft_strdup(command));
	paths = ft_split(path, ':');
	if (!paths)
		return (NULL);
	while (paths[++i] != NULL)
	{
		tmp = ft_str_char_join(paths[i], command, '/');
		if (!tmp)
		{
			free_split(paths);
			perror("minishell");
			exit_error(shell, NULL, EXIT_FAILURE);
		}
		if (access(tmp, F_OK) != -1)
			return (free_split(paths), tmp);
		free(tmp);
	}
	free_split(paths);
	return (NULL);
}

char	*get_path(char *name, t_shell *shell)
{
	char	*path;

	if (ft_strchr(name, '/'))
	{
		check_access(name, shell);
		path = ft_strdup(name);
		if (!path)
		{
			perror("minishell");
			free_shell(shell);
			exit(EXIT_FAILURE);
		}
		return (path);
	}
	path = take_correct_path(name, ht_get(shell->env, "PATH"), shell);
	if (!path)
	{
		ft_putstr_fd(name, 2);
		ft_putstr_fd(": command not found\n", 2);
		free_shell(shell);
		exit(127);
	}
	return (path);
}
