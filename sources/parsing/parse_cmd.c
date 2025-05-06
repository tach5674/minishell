/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggevorgi <sp1tak.gg@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 19:04:37 by ggevorgi          #+#    #+#             */
/*   Updated: 2025/05/06 20:11:35 by ggevorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd *create_cmd_from_tokens(t_token *tokens)
{
	t_cmd *cmd;
	t_token *tmp = tokens;
	t_token *sectmp;
	bool	in_redirection = false;


	cmd = new_cmd_node(NULL);
	while (tmp)
	{
		if (tmp->type == TOKEN_WORD && !in_redirection)
		{
			if (cmd->name == NULL)
				cmd->name = ft_strdup(tmp->value);
			add_arg(cmd, tmp->value);
		}
		else if (tmp->type == TOKEN_REDIR_IN)
		{
			in_redirection = true;
			sectmp = tmp->next;
			if (sectmp && sectmp->type == TOKEN_WORD)
				add_redirection(cmd, REDIR_IN, sectmp->value);
			else
			{
				if (sectmp)
					syntax_error(sectmp->value);
				else
					syntax_error("newline");
				return (NULL);
			}
			tmp = tmp->next;
		}
		else if (tmp->type == TOKEN_REDIR_OUT)
		{
			in_redirection = true;
			sectmp = tmp->next;
			if (sectmp && sectmp->type == TOKEN_WORD)
				add_redirection(cmd, REDIR_OUT, sectmp->value);
			else
			{
				if (sectmp)
					syntax_error(sectmp->value);
				else
					syntax_error("newline");
				return (NULL);
			}
			tmp = tmp->next;
		}
		else if (tmp->type == TOKEN_REDIR_APPEND)
		{
			in_redirection = true;
			sectmp = tmp->next;
			if (sectmp && sectmp->type == TOKEN_WORD)
				add_redirection(cmd, REDIR_APPEND, sectmp->value);
			else
			{
				if (sectmp)
					syntax_error(sectmp->value);
				else
					syntax_error("newline");
				return (NULL);
			}
			tmp = tmp->next;
		}
		else if (tmp->type == TOKEN_HEREDOC)
		{
			in_redirection = true;
			sectmp = tmp->next;
			if (sectmp && sectmp->type == TOKEN_WORD)
				add_redirection(cmd, REDIR_HEREDOC, sectmp->value);
			else
			{
				if (sectmp)
					syntax_error(sectmp->value);
				else
					syntax_error("newline");
				return (NULL);
			}
			tmp = tmp->next;
		}
		else
		{
			*tokens = *tmp;
			break ;	
		}
		in_redirection = false;
		if (tmp)
			tmp = tmp->next;
	}
	return (cmd);
}