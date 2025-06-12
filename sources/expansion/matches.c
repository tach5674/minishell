/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matches.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzohraby <mzohraby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 18:45:19 by mzohraby          #+#    #+#             */
/*   Updated: 2025/06/12 19:16:58 by mzohraby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_quotes_and_match(t_match_state *state)
{
	if (*state->p == '\'' || *state->p == '"')
	{
		if (state->quote == *state->p)
			state->quote = 0;
		else
			state->quote = *state->p;
		state->p++;
		return (1);
	}
	if (*state->p == *state->s)
	{
		state->p++;
		state->s++;
		return (1);
	}
	return (0);
}

static int	handle_star_operations(t_match_state *state)
{
	if (!state->quote && *state->p == '*')
	{
		state->star = state->p;
		state->ss = state->s;
		state->p++;
		return (1);
	}
	if (state->star)
	{
		state->p = state->star + 1;
		state->s = ++state->ss;
		return (1);
	}
	return (0);
}

static int	check_remaining_pattern(const char *p)
{
	while (*p == '*' || *p == '\'' || *p == '"')
		p++;
	while (*p == '/' || *p == '\'' || *p == '"')
		p++;
	return (*p == '\0');
}

static void	init_match_state(t_match_state *state, const char *p, const char *s)
{
	state->p = p;
	state->s = s;
	state->ss = s;
	state->star = NULL;
	state->quote = 0;
}

int	matches(const char *p, const char *s)
{
	t_match_state	state;

	init_match_state(&state, p, s);
	while (*state.s)
	{
		if (handle_quotes_and_match(&state))
			continue ;
		if (handle_star_operations(&state))
			continue ;
		return (0);
	}
	return (check_remaining_pattern(state.p));
}
