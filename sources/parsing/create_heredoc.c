/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggevorgi <sp1tak.gg@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 14:27:19 by ggevorgi          #+#    #+#             */
/*   Updated: 2025/06/02 13:06:04 by ggevorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*create_heredoc_filename(void)
{
	static int	index = 0;
	char		*number_str;
	char		*filename;

	number_str = ft_itoa(index++);
	if (!number_str)
		return (NULL);
	filename = ft_strjoin("/tmp/.heredoc", number_str);
	free(number_str);
	return (filename);
}

int	write_heredoc_to_file(const char *delimiter, const char *filename)
{
	int		fd;
	char	*line;

	fd = open(filename, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (fd == -1)
		return (1);
	while (true)
	{
		ft_putstr_fd("> ", STDOUT_FILENO);
		line = get_next_line(STDIN_FILENO);
		if (!line)
			break ;
		if (!ft_strncmp(line, delimiter, ft_strlen(delimiter) + 1))
		{
			free(line);
			break ;
		}
		ft_putstr_fd(line, fd);
		free(line);
	}
	close(fd);
	return (0);
}

int	run_heredoc_process(const char *delimiter, const char *filename)
{
	pid_t	process_id;
	int		status;

	process_id = fork();
	if (process_id == -1)
		return (false);
	if (!process_id)
	{
		signal(SIGINT, SIG_DFL);
		exit(write_heredoc_to_file(filename, delimiter));
	}		
	else
	{
		waitpid(process_id, &status, 0);
		if (WIFSIGNALED(status))
			return (false);
		else if (WIFEXITED(status) && !(WEXITSTATUS(status)))
			return (true);
	}
	return (false);
}
int	process_heredoc(const char *delimiter, char **out_filename)
{
	char		*filename;
	int			result;
	struct stat	st;

	filename = create_heredoc_filename();
	if (!filename)
		return (-1);
	result = run_heredoc_process(delimiter, filename);

	if (result != 0)
	{
		if (stat(filename, &st) == 0)
		{
			unlink(filename);
		}
		free(filename);
		return (-1);
	}

	*out_filename = filename;
	return (0);
}

void	cleanup_heredoc_files(t_cmd *cmd)
{
	size_t	i;

	i = 0;
	while (i < cmd->redir_count)
	{
		if (cmd->redirections[i]->type == REDIR_HEREDOC)
		{
			unlink(cmd->redirections[i]->target);
			free(cmd->redirections[i]->target);
		}
		i++;
	}
}
