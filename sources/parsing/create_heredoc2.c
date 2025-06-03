/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_heredoc2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikayel <mikayel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 11:35:37 by ggevorgi          #+#    #+#             */
/*   Updated: 2025/06/03 13:22:17 by mikayel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void set_echoctl(bool enable)
// {
// 	struct termios term;

// 	if (tcgetattr(STDIN_FILENO, &term) == -1)
// 		return;
// 	if (enable)
// 		term.c_lflag |= ECHOCTL;
// 	else
// 		term.c_lflag &= ~ECHOCTL;
// 	tcsetattr(STDIN_FILENO, TCSANOW, &term);
// }

void do_child_process(const char *delimiter, const char *filename)
{
	signal(SIGINT, SIG_DFL);
	// setup_signals_child();
	signal(SIGQUIT, SIG_IGN);
	exit(write_heredoc_to_file(delimiter, filename));
}

bool	run_heredoc_process(const char *delimiter, const char *filename)
{
	pid_t	process_id;
	int		status;

	setup_signals_parent_exec();
	process_id = fork();
	if (process_id == -1)
		return (false);
	if (process_id == 0)
	{
		
		do_child_process(delimiter, filename);
	}
	else
	{
		waitpid(process_id, &status, 0);
		if (signal_status == SIGINT)
			write(1, "\n", 1);
		signal_status = 0;
		setup_signals();
		if (WIFSIGNALED(status))
			return (false);
		if (WIFEXITED(status) && WEXITSTATUS(status) == 0)
			return (true); // ✅ Ctrl+D treated as valid
	}
	return (false);
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
