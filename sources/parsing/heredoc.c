/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzohraby <mzohraby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 14:27:19 by ggevorgi          #+#    #+#             */
/*   Updated: 2025/06/13 18:10:08 by mzohraby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	write_heredoc_to_file(const char *delimiter, const char *filename,
		t_shell *shell)
{
	int	fd;

	fd = open(filename, O_CREAT | O_EXCL | O_WRONLY, 0644);
	if (fd == -1)
		return (1);
	read_and_write_heredoc(fd, delimiter, shell);
	close(fd);
	return (0);
}

static char	*create_heredoc_filename(void)
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

static void	do_child_process(const char *delimiter, const char *filename,
		t_shell *shell)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_IGN);
	exit(write_heredoc_to_file(delimiter, filename, shell));
}

static int	run_heredoc_process(const char *delimiter, const char *filename,
		t_shell *shell)
{
	pid_t	process_id;
	int		status;

	setup_signals_parent_exec();
	process_id = fork();
	if (process_id == -1)
		return (EXIT_FAILURE);
	if (process_id == 0)
		do_child_process(delimiter, filename, shell);
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

int	process_heredoc(const char *delimiter, char **out_filename, t_shell *shell)
{
	char	*filename;
	int		result;
	char	*lim;

	lim = ft_strdup(delimiter);
	if (!lim)
		return (EXIT_FAILURE);
	shell->is_heredoc_need_to_expand = remove_quotes(&lim);
	filename = create_heredoc_filename();
	if (!filename)
		return (EXIT_FAILURE);
	result = run_heredoc_process(lim, filename, shell);
	free(lim);
	if (result != 0)
	{
		unlink(filename);
		free(filename);
		return (result);
	}
	*out_filename = filename;
	return (0);
}
