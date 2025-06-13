/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_heredoc2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzohraby <mzohraby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 11:35:37 by ggevorgi          #+#    #+#             */
/*   Updated: 2025/06/13 12:49:47 by mzohraby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_delimiter(char *line, const char *delimiter)
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

static void	print_heredoc_warning(const char *delimiter, int line_number)
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

static int	add_heredoc_file(t_shell *shell, const char *filename)
{
	t_heredoc	*new_node;

	new_node = malloc(sizeof(t_heredoc));
	if (!new_node)
		return (perror("malloc"), 1);
	new_node->filename = strdup(filename);
	if (!new_node->filename)
	{
		free(new_node);
		return (perror("strdup"), 1);
	}
	new_node->next = shell->heredocs;
	shell->heredocs = new_node;
	return (0);
}

t_redirection	*create_heredoc_redirection(const char *delimiter,
		t_shell *shell)
{
	t_redirection	*redir;
	char			*heredoc_path;
	int				status;

	status = process_heredoc(delimiter, &heredoc_path);
	free(shell->last_status_code);
	shell->last_status_code = ft_itoa(status);
	if (!shell->last_status_code)
		throw_err(MALLOC_ERROR);
	if (status == 130)
		return (NULL);
	if (status != 0)
	{
		ft_putstr_fd("heredoc error\n", STDERR_FILENO);
		return (NULL);
	}
	redir = malloc(sizeof(t_redirection));
	if (!redir)
		return (NULL);
	redir->type = REDIR_HEREDOC;
	redir->target = heredoc_path;
	add_heredoc_file(shell, heredoc_path);
	return (redir);
}
