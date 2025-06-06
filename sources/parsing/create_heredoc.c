/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikayel <mikayel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 14:27:19 by ggevorgi          #+#    #+#             */
/*   Updated: 2025/06/06 16:38:51 by mikayel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*create_heredoc_filename(void)
{
	static int	index = 0;
	char		*number_str;
	char		*filename;

	while (1)
	{
		number_str = ft_itoa(index++);
		if (!number_str)
		{
			perror("minishell: ");
			return (NULL);
		}
		filename = ft_strjoin("/tmp/.heredoc", number_str);
		if (!filename)
		{
			perror("minishell: ");
			return (NULL);
		}
		free(number_str);
		if (access(filename, F_OK) != 0)
			return (filename);
		free(filename);
	}
}

int	is_delimiter(char *line, const char *delimiter)
{
	size_t	len;

	if (!line)
		return (0);
	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
	if (ft_strcmp(line, delimiter) == 0)
		return (1);
	if (len > 0 && line[len - 1] == '\0')
		line[len - 1] = '\n';
	return (0);
}

void	print_heredoc_warning(const char *delimiter, int line_number)
{
	ft_putstr_fd("minishell: warning: here-document at line ", STDERR_FILENO);
	ft_putnbr_fd(line_number, STDERR_FILENO);
	ft_putstr_fd(" delimited by end-of-file (wanted `", STDERR_FILENO);
	ft_putstr_fd((char *)delimiter, STDERR_FILENO);
	ft_putstr_fd("')\n", STDERR_FILENO);
}

int	read_and_write_heredoc(int fd, const char *delimiter)
{
	char	*line;
	int		line_number;

	line_number = 1;
	while (1)
	{
		// ft_putstr_fd("> ", STDOUT_FILENO);
		// line = get_next_line(STDIN_FILENO);
		line = readline("> ");
		if (!line)
		{
			print_heredoc_warning(delimiter, line_number);
			break ;
		}
		if (is_delimiter(line, delimiter))
		{
			free(line);
			break ;
		}
		ft_putendl_fd(line, fd);
		free(line);
		line_number++;
	}
	close(fd);
	return (0);
}

int	write_heredoc_to_file(const char *delimiter, const char *filename)
{
	int	fd;

	fd = open(filename, O_CREAT | O_EXCL | O_WRONLY, 0644);
	if (fd == -1)
		return (1);
	read_and_write_heredoc(fd, delimiter);
	close(fd);
	return (0);
}

int	process_heredoc(const char *delimiter, char **out_filename)
{
	char	*filename;
	int		result;

	filename = create_heredoc_filename();
	if (!filename)
		return (1);
	result = run_heredoc_process(delimiter, filename);
	if (!result)
	{
		unlink(filename);
		free(filename);
		write(1, "\n", 1);
		return (130); // SIGINT прерывание
	}
	*out_filename = filename;
	return (0);
}
