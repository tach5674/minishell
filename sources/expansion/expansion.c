/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikayel <mikayel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 12:03:20 by mikayel           #+#    #+#             */
/*   Updated: 2025/06/11 17:48:30 by mikayel          ###   ########.fr       */
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

bool	contains_wildcard(char *str)
{
	char	quote;
	
	quote = 0;
	while (*str)
	{
		if (*str == '\'' || *str == '"')
		{
			if (quote == *str)
				quote = 0;
			else
				quote = *str;
		}
		else if (*str == '*' && quote == 0)
			return (true);
		str++;
	}
	return (false);
}

bool	append_to_arguments(t_cmd *cmd, char **match_list, size_t i, int count)
{
	char **new_args;
	size_t	j;
	size_t	 old_size;
	int	k;
	
	old_size = 0;
	while (cmd->args[old_size])
		old_size++;
	new_args = malloc((old_size + count + 1) * sizeof(char *));
	if (!new_args)
		return (false);
	j = 0;
	while (j < i)
	{
		new_args[j] = cmd->args[j];
		j++;
	}
	k = 0;
	while (k < count)
	{
		new_args[j] = match_list[k];
		j++;
		k++;
	}
	free(cmd->args[i]);
	i++;
	while (i < old_size)
	{
		new_args[j] = cmd->args[i];
		i++;
		j++;
	}
	new_args[j] = NULL;
	free(cmd->args);
	free(match_list);
	cmd->args = new_args;
	return (true);	
}

bool expand_wildcards(t_cmd *cmd, size_t *i)
{
	int count;
	char **match_list;
	bool	show_hidden;
	bool	only_dir;
	int		len;
	
	if (!contains_wildcard(cmd->args[*i]))
		return (true);
	count = 0;
	show_hidden = false;
	only_dir = false;
	if (*cmd->args[*i] == '.')
		show_hidden = true;
	len = ft_strlen(cmd->args[*i]);
	while (len--)
	{
		if ((cmd->args[*i])[len] == '/')
		{
			only_dir = true;
			break;
		}
		else if ((cmd->args[*i])[len] == '\'' || (cmd->args[*i])[len] == '"')
			continue;
		else
			break ;
	}
	match_list = wildcard_expand((cmd->args[*i]), &count, show_hidden, only_dir);
	if (!match_list)
		return (false);
	if (append_to_arguments(cmd, match_list, *i, count) == false)
		return (false);
	*i += count - 1;
	return (true);
}

bool expand_wildcards_redir(char **str)
{
	int count;
	char **match_list;
	bool	show_hidden;
	bool	only_dir;
	int		len;
	
	if (!contains_wildcard(*str))
		return (true);
	count = 0;
	show_hidden = false;
	only_dir = false;
	if (**str == '.')
		show_hidden = true;
	len = ft_strlen(*str);
	while (len--)
	{
		if ((*str)[len] == '/')
		{
			only_dir = true;
			break;
		}
		else if ((*str)[len] == '\'' || (*str)[len] == '"')
			continue;
		else
			break ;
	}
	match_list = wildcard_expand(*str, &count, show_hidden, only_dir);
	if (!match_list)
		return (false);
	if (count > 1)
	{
		ft_putstr_fd("minishell: *: ambigous redirect\n", 2);
		free_list(match_list, count);
		return (false);
	}
	free(*str);
	*str = match_list[0];
	free(match_list);
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
		if (expand_wildcards(cmd, &i) == false)
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
		if (expand_wildcards_redir(&cmd->redirections[i]->target) == false)
		{
			if (errno)
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