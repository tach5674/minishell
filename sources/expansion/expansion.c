/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikayel <mikayel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 12:03:20 by mikayel           #+#    #+#             */
/*   Updated: 2025/06/10 14:26:47 by mikayel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	check_if_quotes(char *str, int *in_quotes, int i)
{
	if (str[i] == '\'')
	{
		if (*in_quotes == 0)
			*in_quotes = 1;
		else if (*in_quotes == 1)
			*in_quotes = 0;
		return (true);
	}
	else if (str[i] == '"')
	{
		if (*in_quotes == 0)
			*in_quotes = 2;
		else if (*in_quotes == 2)
			*in_quotes = 0;
		return (true);
	}
	return (false);
}

static int	remove_quote(char **str, int i, int *in_quotes)
{
	char	*temp;
	char	*temp1;
	int		check;
	
	if ((*str)[i] == '\'')
		check = 1;
	else
		check = 2; 
	if (*in_quotes != (3 - check))
	{
		temp = ft_strndup(*str, i);
		if (!temp)
			return (-1);
		temp1 = ft_strjoin(temp, *str + i + 1);
		if (!temp1)
		{
			free(temp);
			return (-1);
		}
		free(*str);
		*str = temp1;
		free(temp);
		*in_quotes = check - *in_quotes;
		return (1);
	}
	return (0);
}

static bool	remove_quotes(char **str)
{
	int	in_quotes;
	int	i;
	int	res;
	
	i = 0;
	in_quotes = 0;
	while ((*str)[i])
	{
		if ((*str)[i] == '\'' || (*str)[i] == '"')
		{
			res = remove_quote(str, i, &in_quotes);
			if (res == -1)
				return (false);
			else if (res == 0)
				i++;
			continue ;
		}
		i++;
	}
	return (true);
}

bool    apply_expansions(t_cmd *cmd, t_shell *shell)
{
    size_t	i;

	i = 0;
    while (cmd->args[i])
	{
		if (expand_tilde(&cmd->args[i], shell->env) == false)
		{
			perror("minishell");
			return (false);
		}
		if (expand_arguments(&cmd->args[i], shell) == false)
		{
			perror("minishell");
			return (false);
		}
		if (remove_quotes(&cmd->args[i]) == false)
		{
			perror("minishell");
			return (false);
		}
		i++;
	}
	i = 0;
	while (i < cmd->redir_count)
	{
		if (expand_tilde(&cmd->redirections[i]->target, shell->env) == false)
		{
			perror("minishell");
			return (false);
		}
		if (expand_arguments(&cmd->redirections[i]->target, shell) == false)
		{
			perror("minishell");
			return (false);
		}
		if (remove_quotes(&cmd->redirections[i]->target) == false)
		{
			perror("minishell");
			return (false);
		}
		i++;
	}
	return (true);
}