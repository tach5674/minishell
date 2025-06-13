/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzohraby <mzohraby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 13:54:45 by mzohraby          #+#    #+#             */
/*   Updated: 2025/06/13 12:45:01 by mzohraby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "minishell.h"

t_cmd	*create_cmd_from_tokens(t_token *tokens, t_shell *shell);
t_ast	*parse(t_token **tokens, t_shell *shell);

#endif