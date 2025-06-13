/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzohraby <mzohraby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 17:42:15 by ggevorgi          #+#    #+#             */
/*   Updated: 2025/06/13 13:14:33 by mzohraby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_operator(char c)
{
	return (c == '|' || c == '&' || c == '<' || c == '>' || c == '('
		|| c == ')');
}

void	free_tokens(t_token *tokens)
{
	t_token	*tmp;

	while (tokens)
	{
		tmp = tokens->next;
		free(tokens->value);
		free(tokens);
		tokens = tmp;
	}
}

t_token_type	oper_type(const char *s, int *len)
{
	if (s[0] == '&' && s[1] == '&')
		return (*len = 2, TOKEN_AND);
	if (s[0] == '|' && s[1] == '|')
		return (*len = 2, TOKEN_OR);
	if (s[0] == '<' && s[1] == '<')
		return (*len = 2, TOKEN_HEREDOC);
	if (s[0] == '>' && s[1] == '>')
		return (*len = 2, TOKEN_REDIR_APPEND);
	if (s[0] == '|')
		return (*len = 1, TOKEN_PIPE);
	if (s[0] == '&')
		return (*len = 1, TOKEN_AND);
	if (s[0] == '<')
		return (*len = 1, TOKEN_REDIR_IN);
	if (s[0] == '>')
		return (*len = 1, TOKEN_REDIR_OUT);
	if (s[0] == '(')
		return (*len = 1, TOKEN_PAREN_LEFT);
	if (s[0] == ')')
		return (*len = 1, TOKEN_PAREN_RIGHT);
	return (*len = 0, TOKEN_EOF);
}
