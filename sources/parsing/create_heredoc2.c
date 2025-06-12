/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_heredoc2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzohraby <mzohraby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 11:35:37 by ggevorgi          #+#    #+#             */
/*   Updated: 2025/06/12 17:33:24 by mzohraby         ###   ########.fr       */
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
			return (errno = 0, filename);
		free(filename);
	}
}

void	do_child_process(const char *delimiter, const char *filename)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_IGN);
	exit(write_heredoc_to_file(delimiter, filename));
}

int	run_heredoc_process(const char *delimiter, const char *filename)
{
	pid_t	process_id;
	int		status;

	setup_signals_parent_exec();
	process_id = fork();
	if (process_id == -1)
		return (EXIT_FAILURE);
	if (process_id == 0)
		do_child_process(delimiter, filename);
	else
	{
		waitpid(process_id, &status, 0);
		setup_signals();
		if (WIFSIGNALED(status))
		{
			g_signal_status = WTERMSIG(status);
			return (WTERMSIG(status) + 128);
		}
		if (WIFEXITED(status))
			return (WEXITSTATUS(status));
	}
	return (EXIT_FAILURE);
}

int	add_heredoc_file(t_shell *shell, const char *filename)
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
