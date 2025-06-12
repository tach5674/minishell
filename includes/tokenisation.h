/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenisation.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzohraby <mzohraby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 13:30:30 by mzohraby          #+#    #+#             */
/*   Updated: 2025/06/12 14:19:04 by mzohraby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENISATION_H
# define TOKENISATION_H

# include "minishell.h"

t_token_type	oper_type(const char *s, int *len);
char			*parse_word(const char *line, int *i);
t_token			*ft_lstnew_token(t_token_type type, char *value);
t_token			*tokenize(char *line, int i);
void			ft_lstadd_back_token(t_token **lst, t_token *new_token);
bool			is_operator(char c);
void			free_tokens(t_token *tokens);

#endif