/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikayel <mikayel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 11:26:09 by mikayel           #+#    #+#             */
/*   Updated: 2025/05/29 15:51:11 by mikayel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

#include "minishell.h"

void	execute_commands(t_shell *shell_data);
int     execute_ast(t_ast *ast, t_shell *shell_data, bool wait, int extra_fd);
int     execute_cmd(t_cmd *cmd, t_shell *shell_data, bool wait, int extra_fd);
void	redirect_files(t_redirection *redir);
void	apply_redirections(t_cmd *cmd, int extra_fd);
void	set_pipe_redirections(t_ast *ast, int fd, t_redir_type type);
bool	syntax_error_check(t_token *tokens);
int		get_exit_code(int status);
void    exit_error(char *filename);
int	    check_if_builtin(char *cmd);
int		execute_builtin(t_cmd *cmd, t_shell *shell_data, int cmd_num, int extra_fd);

// has to be removed

void	print_ast_node(t_ast *node, int depth);
void	print_ast(t_ast *ast);
const char	*token_type_str(t_token_type type);
void	print_tokens(t_token *list);

#endif