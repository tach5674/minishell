/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzohraby <mzohraby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 13:52:26 by mzohraby          #+#    #+#             */
/*   Updated: 2025/06/13 18:10:56 by mzohraby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEREDOC_H
# define HEREDOC_H

# include "minishell.h"

int				read_and_write_heredoc(int fd, const char *delimiter,
					t_shell *shell);
int				process_heredoc(const char *delimiter, char **out_filename,
					t_shell *shell);
void			cleanup_heredocs(t_shell *shell);
t_redirection	*create_heredoc_redirection(const char *delimiter,
					t_shell *shell);
#endif