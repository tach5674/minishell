/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzohraby <mzohraby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 12:03:20 by mikayel           #+#    #+#             */
/*   Updated: 2025/06/12 17:58:18 by mzohraby         ###   ########.fr       */
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

bool	expand_commands(t_cmd *cmd, t_shell *shell)
{
	size_t	i;

	i = 0;
	while (cmd->args[i])
	{
		if (expand_tilde(&cmd->args[i], shell->env) == false)
			return (perror("minishell"), false);
		if (expand_arguments(&cmd->args[i], shell) == false)
			return (perror("minishell"), false);
		if (expand_wildcards(cmd, &i) == false)
			return (perror("minishell"), false);
		if (remove_quotes(&cmd->args[i]) == false)
			return (perror("minishell"), false);
		i++;
	}
	return (true);
}

bool	expand_redirections(t_cmd *cmd, t_shell *shell)
{
	size_t	i;

	i = 0;
	while (i < cmd->redir_count)
	{
		if (expand_tilde(&cmd->redirections[i]->target, shell->env) == false)
			return (perror("minishell"), false);
		if (expand_arguments(&cmd->redirections[i]->target, shell) == false)
			return (perror("minishell"), false);
		if (expand_wildcards_redir(&cmd->redirections[i]->target) == false)
		{
			if (errno)
				perror("minishell");
			return (false);
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
