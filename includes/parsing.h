/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzohraby <mzohraby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 13:54:45 by mzohraby          #+#    #+#             */
/*   Updated: 2025/06/12 14:16:25 by mzohraby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "minishell.h"

int		handle_redirect(t_token **tmp, t_cmd *cmd, t_redir_type type);
void	handle_word_token(t_cmd *cmd, t_token *token);
t_cmd	*create_cmd_from_tokens(t_token *tokens, t_shell *shell);
t_ast	*parse_pipeline(t_token **tokens, t_shell *shell);
t_ast	*parse_command_or_subshell(t_token **tokens, t_shell *shell);
t_ast	*parse_subshell(t_token **tokens, t_shell *shell);
t_ast	*parse_and_or(t_token **tokens, t_shell *shell);
t_ast	*parse(t_token **tokens, t_shell *shell);

#endif