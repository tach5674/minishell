/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggevorgi <sp1tak.gg@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 14:27:19 by ggevorgi          #+#    #+#             */
/*   Updated: 2025/05/29 13:51:46 by ggevorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*make_heredoc_filename(int index)
{
	char	*number_str;
	char	*filename;

	number_str = ft_itoa(index);
	if (!number_str)
		return (NULL);
	filename = ft_strjoin("/tmp/.heredoc", number_str);
	free(number_str);
	return (filename);
}

int	write_heredoc_to_file(const char *delimiter, const char *filename)
{
	int		fd_write;
	char	*line;

	fd_write = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (fd_write < 0)
		return (-1);
	while (1)
	{
		write(1, "> ", 2);
		line = get_next_line(STDIN_FILENO);
		if (!line)
			break;
		if (ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0
			&& (line[ft_strlen(delimiter)] == '\n' || line[ft_strlen(delimiter)] == '\0'))
		{
			free(line);
			break;
		}
		write(fd_write, line, ft_strlen(line));
		free(line);
	}
	close(fd_write);
	return (0);
}

int	process_heredoc(const char *delimiter, char **out_filename)
{
	static int	index = 0;
	char		*filename;

	filename = make_heredoc_filename(index++);
	if (!filename)
		return (-1);
	if (write_heredoc_to_file(delimiter, filename) != 0)
	{
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
