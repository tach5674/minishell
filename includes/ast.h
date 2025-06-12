/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzohraby <mzohraby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 13:59:00 by mzohraby          #+#    #+#             */
/*   Updated: 2025/06/12 14:19:48 by mzohraby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

# include "minishell.h"

void			free_redirections(t_redirection **redirs, size_t count);
void			free_cmd(t_cmd *cmd);
void			free_ast(t_ast *ast);
t_ast			*new_ast_node(t_ast_node_type type);
t_cmd			*new_cmd_node(char *name, t_shell *shell);
void			add_arg(t_cmd *cmd, char *arg);
t_redirection	*create_heredoc_redirection(const char *delimiter,
					t_shell *shell);
t_redirection	*create_redirection(t_redir_type type, const char *target,
					t_shell *shell);
void			add_redirection(t_cmd *cmd, t_redirection *redir);

#endif