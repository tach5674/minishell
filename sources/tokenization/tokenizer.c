/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzohraby <mzohraby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 17:44:49 by ggevorgi          #+#    #+#             */
/*   Updated: 2025/06/14 16:02:06 by mzohraby         ###   ########.fr       */
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

static t_token	*ft_lstnew_token(t_token_type type, char *value)
{
	t_token	*nnode;

	nnode = (t_token *)malloc(sizeof(t_token));
	if (!nnode)
		return (NULL);
	nnode->type = type;
	nnode->value = value;
	nnode->next = NULL;
	return (nnode);
}

static bool	add_back_token(t_token **lst, t_token *new_token)
{
	t_token	*lstcpy;

	if (!lst || !new_token)
		return (false);
	if (!*lst)
	{
		*lst = new_token;
		return (true);
	}
	lstcpy = *lst;
	while (lstcpy->next)
		lstcpy = lstcpy->next;
	lstcpy->next = new_token;
	return (true);
}

static bool	tokenize_helper(t_token **list, char *line, int *i)
{
	char	*word;

	word = parse_word(line, i);
	if (!add_back_token(list, ft_lstnew_token(TOKEN_WORD, word)))
		return (perror("minishell"), free_tokens(*list), false);
	return (true);
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
			if (!add_back_token(&list, ft_lstnew_token(type, word)))
				return (perror("minishell"), free_tokens(list), NULL);
			i += len;
		}
		else
		{
			if (tokenize_helper(&list, line, &i) == false)
				return (NULL);
		}
	}
	return (list);
}
