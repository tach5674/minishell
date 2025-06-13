/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzohraby <mzohraby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 13:30:30 by mzohraby          #+#    #+#             */
/*   Updated: 2025/06/13 13:30:18 by mzohraby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZATION_H
# define TOKENIZATION_H

# include "minishell.h"

t_token_type	oper_type(const char *s, int *len);
t_token			*tokenize(char *line, int i);
bool			is_operator(char c);
void			free_tokens(t_token *tokens);

#endif