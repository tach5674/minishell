/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggevorgi <sp1tak.gg@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 11:49:47 by ggevorgi          #+#    #+#             */
/*   Updated: 2025/04/24 17:50:48 by ggevorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_unmatched_quotes(const char *line)
{
	char	quote;

	quote = 0;
	while (*line)
	{
		if ((*line == '\'' || *line == '"') && quote == 0)
			quote = *line;
		else if (*line == quote)
			quote = 0;
		line++;
	}
	return (quote != 0);
}

char	*read_prompt(void)
{
	char	*line;
	char	*full;
	char	*tmp;

	line = readline("\033[1;32mminishell$ \033[0m");
	full = line;
	while (line && check_unmatched_quotes(full))
	{
		line = readline("> ");
		if (!line)
		{
			ft_putstr_fd("minishell: unexpected EOF while"
				"looking for matching `\"\'\n", 2);
			free(full);
			return (NULL);
		}
		tmp = ft_strjoin(full, "\n");
		free(full);
		full = ft_strjoin(tmp, line);
		free(tmp);
		free(line);
	}
	return (full);
}
