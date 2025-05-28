/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikayel <mikayel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 11:26:09 by mikayel           #+#    #+#             */
/*   Updated: 2025/05/27 20:09:41 by mikayel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

#include "minishell.h"

void	execute_commands(t_shell *shell_data);
int     execute_ast(t_ast *ast, t_shell *shell_data, bool wait, int extra_fd);
void	redirect_files(t_redirection *redir);
void	apply_redirections(t_cmd *cmd, int extra_fd);
void	set_pipe_redirections(t_ast *ast, int fd, t_redir_type type);
bool	syntax_error_check(t_token *tokens);

// has to be removed

void	print_ast_node(t_ast *node, int depth);
void	print_ast(t_ast *ast);
const char	*token_type_str(t_token_type type);
void	print_tokens(t_token *list);

#endif