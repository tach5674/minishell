/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzohraby <mzohraby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 14:55:36 by ggevorgi          #+#    #+#             */
/*   Updated: 2025/06/14 13:27:21 by mzohraby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	check_if_quotes(char *str, char *in_quotes, int i)
{
	if (str[i] == '\'' || str[i] == '"')
	{
		if (*in_quotes == 0)
			*in_quotes = str[i];
		else if (*in_quotes == str[i])
			*in_quotes = 0;
		return (true);
	}
	return (false);
}

static bool	expand_empty(t_cmd *cmd, int j, t_ht *env)
{
	int     i;
	
	if (ft_isdigit((cmd->args[j])[1]))
	{
		if (ft_strlen((cmd->args[j])) == 2)
		{
			if ((cmd->args[j])[1] == '0')
				return (false);
			return (append_to_arguments(cmd, NULL, j, 0));
		}
		return (false);
	}
	i = 1;
	while ((cmd->args[j])[i])
	{
		if (!ft_isalnum((cmd->args[j])[i]) && (cmd->args[j])[i] != '_')
				break ;
		i++;
	}
	if ((cmd->args[j])[i] == '\0')
	{
		if (ht_get(env, cmd->args[j] + 1) == false)
			return (append_to_arguments(cmd, NULL, j, 0));
	}
	return (false);
}

static bool	expand_empty_redir(char *str, t_ht *env)
{
	int     i;
	
	if (ft_isdigit(str[1]))
	{
		if (ft_strlen(str) == 2)
		{
			if (str[1] == '0')
				return (false);
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(str, 2);
			ft_putstr_fd(": ambigous redirect\n", 2);
			return (true);
		}
		return (false);
	}
	i = 1;
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
				break ;
		i++;
	}
	if (str[i] == '\0')
	{
		if (ht_get(env, str + 1) == false)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(str, 2);
			ft_putstr_fd(": ambigous redirect\n", 2);
			return (true);
		}
	}
	return (false);
}

static bool     expand_commands(t_cmd *cmd, t_shell *shell)
{
	size_t  i;
	int		check;
	
	i = 0;
	while (cmd->args[i])
	{
		if (cmd->args[i][0] == '$')
		{
			check = expand_empty(cmd, i, shell->env);
			if (check == false)
			{
				if (errno)
					return (errno = 0, perror("minishell"), false);
			}
			else
				continue ;
		}
		if (expand_tilde(&cmd->args[i], shell->env) == false)
			return (perror("minishell"), false);
		if (expand_arguments(&cmd->args[i], shell, false) == false)
			return (perror("minishell"), false);
		if (expand_wildcards(cmd, &i) == false)
			return (perror("minishell"), false);
		if (remove_quotes(&cmd->args[i]) == false)
			return (perror("minishell"), false);
		i++;
	}
	return (true);
}

static bool	expand_redirections(t_cmd *cmd, t_shell *shell)
{
	size_t	i;

	i = 0;
	while (i < cmd->redir_count)
	{
		if (cmd->redirections[i]->target[0] == '$')
		{
			if (expand_empty_redir(cmd->redirections[i]->target, shell->env))
				return (false);
		}
		if (expand_tilde(&cmd->redirections[i]->target, shell->env) == false)
			return (perror("minishell"), false);
		if (expand_arguments(&cmd->redirections[i]->target, shell,
				false) == false)
			return (perror("minishell"), false);
		if (expand_wildcards_redir(&cmd->redirections[i]->target) == false)
		{
			if (errno)
				perror("minishell");
			return (errno = 0, false);
		}
		if (remove_quotes(&cmd->redirections[i]->target) == false)
			return (perror("minishell"), false);
		i++;
	}
	return (true);
}

bool	apply_expansions(t_cmd *cmd, t_shell *shell)
{
	if (expand_commands(cmd, shell) == false)
		return (false);
	if (expand_redirections(cmd, shell) == false)
		return (false);
	return (true);
}
