/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzohraby <mzohraby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 13:52:26 by mzohraby          #+#    #+#             */
/*   Updated: 2025/06/12 17:21:12 by mzohraby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEREDOC_H
# define HEREDOC_H

# include "minishell.h"

char			*create_heredoc_filename(void);
int				is_delimiter(char *line, const char *delimiter);
void			print_heredoc_warning(const char *delimiter, int line_number);
int				read_and_write_heredoc(int fd, const char *delimiter);
int				write_heredoc_to_file(const char *delimiter,
					const char *filename);
int				process_heredoc(const char *delimiter, char **out_filename);
void			do_child_process(const char *delimiter, const char *filename);
int				run_heredoc_process(const char *delimiter,
					const char *filename);
int				add_heredoc_file(t_shell *shell, const char *filename);
void			cleanup_heredocs(t_shell *shell);
t_redirection	*create_heredoc_redirection(const char *delimiter,
					t_shell *shell);
#endif