/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggevorgi <sp1tak.gg@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 17:42:15 by ggevorgi          #+#    #+#             */
/*   Updated: 2025/05/13 17:02:57 by ggevorgi         ###   ########.fr       */
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

void	ft_lstadd_back_token(t_token **lst, t_token *new)
{
	t_token	*lstcpy;

	if (!lst || !new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	lstcpy = *lst;
	while (lstcpy->next)
		lstcpy = lstcpy->next;
	lstcpy->next = new;
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
