/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzohraby <mzohraby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 17:42:15 by ggevorgi          #+#    #+#             */
/*   Updated: 2025/06/12 13:32:49 by mzohraby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*ft_lstnew_token(t_token_type type, char *value)
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

void	ft_lstadd_back_token(t_token **lst, t_token *new_token)
{
	t_token	*lstcpy;

	if (!lst || !new_token)
		return ;
	if (!*lst)
	{
		*lst = new_token;
		return ;
	}
	lstcpy = *lst;
	while (lstcpy->next)
		lstcpy = lstcpy->next;
	lstcpy->next = new_token;
}

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
