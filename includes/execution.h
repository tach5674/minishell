/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikayel <mikayel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 11:26:09 by mikayel           #+#    #+#             */
/*   Updated: 2025/06/13 20:26:37 by mikayel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "minishell.h"

void		execute_commands(t_shell *shell_data);
int			execute_cmd(t_cmd *cmd, t_shell *shell_data, bool wait,
				int extra_fd);
int			apply_redirections(t_cmd *cmd, int extra_fd);
void		set_pipe_redirections(t_ast *ast, int fd, t_redir_type type);
bool		syntax_error_check(t_token *tokens);
int			get_exit_code(int status);
int			check_if_builtin(char *cmd);
int			execute_builtin(t_cmd *cmd, t_shell *shell_data, int cmd_num,
				int extra_fd);
char		*get_path(char *name, t_shell *shell);
int			handle_error(char *name);
void		exit_error(t_shell *shell, char *cmd_path, int exit_code);
void		set_in_subshell(t_ast *ast);
#endif