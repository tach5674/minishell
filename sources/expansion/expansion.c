/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzohraby <mzohraby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 14:55:36 by ggevorgi          #+#    #+#             */
/*   Updated: 2025/06/17 16:57:41 by mzohraby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	expand_empty_redir(char *str, t_ht *env)
{
	int	i;

	if (ft_isdigit(str[1]))
	{
		if (ft_strlen(str) == 2)
			return (print_error_expansions(str), true);
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
			return (print_error_expansions(str), true);
	}
	return (false);
}

static bool	process_command_argument(t_cmd *cmd, size_t *i, t_shell *shell)
{
	if (expand_arguments(&cmd->args[*i], shell, false) == false)
		return (perror("minishell"), false);
	if (split_arguments(cmd, *i) == false)
		return (false);
	if (expand_wildcards(cmd, i) == false)
		return (false);
	if (remove_quotes(&cmd->args[(*i)++]) == false)
		return (perror("minishell"), false);
	return (true);
}

static bool	expand_commands(t_cmd *cmd, t_shell *shell)
{
	size_t	i;
	int		check;

	i = 0;
	while (cmd->args[i])
	{
		if (expand_tilde(&cmd->args[i], shell->env) == false)
			return (perror("minishell"), false);
		if (cmd->args[i][0] == '$' && cmd->args[i][1] != '?'
			&& cmd->args[i][1] != '0' && cmd->args[i][1])
		{
			check = expand_empty(cmd, i, shell->env);
			if (check == false)
				return (false);
			else if (check == 1)
				continue ;
		}
		if (!process_command_argument(cmd, &i, shell))
			return (false);
	}
	return (true);
}

static bool	expand_redirections(t_cmd *cmd, t_shell *shell)
{
	size_t	i;

	i = 0;
	while (i < cmd->redir_count)
	{
		if (expand_tilde(&cmd->redirections[i]->target, shell->env) == false)
			return (perror("minishell"), false);
		if (cmd->redirections[i]->target[0] == '$'
			&& cmd->redirections[i]->target[1] != '?'
			&& cmd->redirections[i]->target[1] != '0'
			&& cmd->redirections[i]->target[1])
		{
			if (expand_empty_redir(cmd->redirections[i]->target, shell->env))
				return (false);
		}
		if (!expand_arguments(&cmd->redirections[i]->target, shell, false))
			return (perror("minishell"), false);
		if (split_arguments_redir(cmd->redirections[i]->target) == false)
			return (false);
		if (expand_wildcards_redir(&cmd->redirections[i]->target) == false)
			return (false);
		if (remove_quotes(&cmd->redirections[i++]->target) == false)
			return (perror("minishell"), false);
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
