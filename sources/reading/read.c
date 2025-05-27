/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikayel <mikayel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 11:49:47 by ggevorgi          #+#    #+#             */
/*   Updated: 2025/05/27 19:30:26 by mikayel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static int	check_unmatched_quotes(const char *line)
// {
// 	char	quote;

// 	quote = 0;
// 	while (*line)
// 	{
// 		if ((*line == '\'' || *line == '"') && quote == 0)
// 			quote = *line;
// 		else if (*line == quote)
// 			quote = 0;
// 		line++;
// 	}
// 	return (quote != 0);
// }

// static int	check_unmatched_operands(const char *line)
// {
// 	while (*line)
// 		line++;
// 	line--;
// 	if (*line == '&' || *line == '|')
// 		return (true);
// 	return (false);
// }

// char	*unmatched_handler(int	unmatched_case, char *full)
// {
// 	if (unmatched_case == 1)
// 	{
// 		ft_putstr_fd("minishell: unexpected EOF while "
// 		"looking for matching `\"\'\n", 2);
// 		ft_putstr_fd("minishell: syntax error:"
// 		"unexpected end of file\n", 2);
// 		free(full);
// 		return (read_prompt());
// 	}
// 	else
// 	{
// 		ft_putstr_fd("minishell: syntax error:"
// 		"unexpected end of file\n", 2);
// 		free(full);
// 		return (NULL);
// 	}
// }

// char	*read_prompt(void)
// {
// 	char	*full;
// 	char	*line;
// 	char 	*tmp;
// 	int		missmatch_case;
	
// 	full = readline("\033[1;32mminishell$ \033[0m");
// 	while (full)
// 	{
// 		if (check_unmatched_quotes(full))
// 			missmatch_case = 1;
// 		else if (check_unmatched_operands(full))
// 			missmatch_case = 2;
// 		else
// 			break;
// 		line = readline("> ");
// 		if (!line)
// 		return (unmatched_handler(missmatch_case, full));
// 		tmp = ft_strjoin(full, "\n");
// 		free(full);
// 		full = ft_strjoin(tmp, line);
// 		free(tmp);
// 		free(line);
// 	}
// 	return (full);
// }
