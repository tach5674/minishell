/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error_checker.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggevorgi <sp1tak.gg@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 14:55:19 by ggevorgi          #+#    #+#             */
/*   Updated: 2025/06/13 14:55:20 by ggevorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	check_unmatched_quotes(const char *word)
{
	char	quote;

	quote = 0;
	while (*word)
	{
		if ((*word == '\'' || *word == '"') && quote == 0)
			quote = *word;
		else if (*word == quote)
			quote = 0;
		word++;
	}
	return (quote != 0);
}

static bool	word_syntax_check(t_token *tokens, t_token_type last_token_t)
{
	if (check_unmatched_quotes(tokens->value))
	{
		syntax_error("newline");
		return (true);
	}
	else if (last_token_t == TOKEN_PAREN_RIGHT)
	{
		syntax_error(tokens->value);
		return (true);
	}
	return (false);
}

static bool	double_operand_syntax_check(t_token *tokens,
		t_token_type last_token_t, int *scope_count)
{
	if (last_token_t != TOKEN_WORD && last_token_t != TOKEN_PAREN_RIGHT)
	{
		syntax_error(tokens->value);
		return (true);
	}
	if (tokens->type == TOKEN_PAREN_RIGHT)
	{
		(*scope_count)--;
		if (*scope_count < 0)
		{
			syntax_error(tokens->value);
			return (true);
		}
	}
	if ((tokens->type == TOKEN_PIPE || tokens->type == TOKEN_AND
			|| tokens->type == TOKEN_OR) && !tokens->next)
	{
		syntax_error("newline");
		return (true);
	}
	return (false);
}

static bool	syntax_error_check_helper(t_token *tokens,
		t_token_type last_token_t, int *scope_count)
{
	while (tokens)
	{
		if (tokens->type == TOKEN_WORD)
		{
			if (word_syntax_check(tokens, last_token_t) == true)
				return (true);
		}
		else if (tokens->type == TOKEN_PIPE || tokens->type == TOKEN_AND
			|| tokens->type == TOKEN_OR || tokens->type == TOKEN_PAREN_RIGHT)
		{
			if (double_operand_syntax_check(tokens, last_token_t,
					scope_count) == true)
				return (true);
		}
		else if (tokens->type == TOKEN_PAREN_LEFT)
		{
			(*scope_count)++;
			if (last_token_t != TOKEN_PIPE && last_token_t != TOKEN_AND
				&& last_token_t != TOKEN_OR && last_token_t != TOKEN_PAREN_LEFT)
				return (syntax_error(tokens->value), true);
		}
		last_token_t = tokens->type;
		tokens = tokens->next;
	}
	return (false);
}

bool	syntax_error_check(t_token *tokens)
{
	t_token_type	last_token_t;
	int				scope_count;

	scope_count = 0;
	if (tokens->type == TOKEN_PIPE || tokens->type == TOKEN_OR
		|| tokens->type == TOKEN_AND || tokens->type == TOKEN_PAREN_RIGHT)
		return (syntax_error(tokens->value), true);
	if (tokens->type == TOKEN_PAREN_LEFT)
		scope_count++;
	if (tokens->type == TOKEN_WORD && check_unmatched_quotes(tokens->value))
		return (syntax_error("newline"), true);
	last_token_t = tokens->type;
	tokens = tokens->next;
	if (syntax_error_check_helper(tokens, last_token_t, &scope_count))
		return (true);
	if (scope_count > 0)
		return (syntax_error("newline"), true);
	return (false);
}
