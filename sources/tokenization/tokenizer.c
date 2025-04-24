/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggevorgi <sp1tak.gg@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 17:44:49 by ggevorgi          #+#    #+#             */
/*   Updated: 2025/04/24 18:04:54 by ggevorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*parse_word(const char *line, int *i)
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

t_token	*tokenize(char *line, int i)
{
	int				len;
	char			*word;
	t_token			*list;
	t_token_type	type;

	list = NULL;
	while (line[i])
	{
		if (ft_isspace(line[i]))
			i++;
		else if (is_operator(line[i]))
		{
			type = oper_type(&line[i], &len);
			word = ft_substr(line, i, len);
			ft_lstadd_back_token(&list, ft_lstnew_token(type, word));
			i += len;
		}
		else
		{
			word = parse_word(line, &i);
			ft_lstadd_back_token(&list, ft_lstnew_token(TOKEN_WORD, word));
		}
	}
	return (list);
}
