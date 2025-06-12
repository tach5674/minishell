/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzohraby <mzohraby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 17:44:49 by ggevorgi          #+#    #+#             */
/*   Updated: 2025/06/12 13:11:31 by mzohraby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

char	*parse_word(const char *line, int *i)
{
	int		start;
	char	quote;

	start = *i;
	quote = 0;
	while (line[*i])
	{
		if (!quote && (line[*i] == '\'' || line[*i] == '"'))
			quote = line[(*i)++];
		else if (quote && line[*i] == quote)
		{
			(*i)++;
			quote = 0;
		}
		else if (!quote && (line[*i] == ' ' || is_operator(line[*i])))
			break ;
		else
			(*i)++;
	}
	return (ft_substr(line, start, *i - start));
}
