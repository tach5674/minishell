/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggevorgi <sp1tak.gg@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 19:04:37 by ggevorgi          #+#    #+#             */
/*   Updated: 2025/05/28 15:47:22 by ggevorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_redirect(t_token **tmp, t_cmd *cmd, t_redir_type type)
{
	t_token	*next;

	next = (*tmp)->next;
	if (!next || next->type != TOKEN_WORD)
	{
		if (next)
			syntax_error(next->value);
		else
			syntax_error("newline");
		return (1);
	}
	add_redirection(cmd, create_redirection(type, next->value));
	*tmp = next;
	return (0);
}

void	handle_word_token(t_cmd *cmd, t_token *token)
{
	if (!cmd->name)
		cmd->name = ft_strdup(token->value);
	add_arg(cmd, token->value);
}

t_cmd	*create_cmd_from_tokens(t_token *tokens)
{
	t_cmd	*cmd;
	t_token	*tmp;

	tmp = tokens;
	cmd = new_cmd_node(NULL);
	while (tmp && tmp->type != TOKEN_PIPE && tmp->type != TOKEN_AND
		&& tmp->type != TOKEN_OR && tmp->type != TOKEN_PAREN_RIGHT)
	{
		if (tmp->type == TOKEN_WORD)
			handle_word_token(cmd, tmp);
		else if (tmp->type == TOKEN_REDIR_IN
			&& handle_redirect(&tmp, cmd, REDIR_IN))
			return (free_cmd(cmd), NULL);
		else if (tmp->type == TOKEN_REDIR_OUT
			&& handle_redirect(&tmp, cmd, REDIR_OUT))
			return (free_cmd(cmd), NULL);
		else if (tmp->type == TOKEN_REDIR_APPEND
			&& handle_redirect(&tmp, cmd, REDIR_APPEND))
			return (free_cmd(cmd), NULL);
		else if (tmp->type == TOKEN_HEREDOC
			&& handle_redirect(&tmp, cmd, REDIR_HEREDOC))
			return (free_cmd(cmd), NULL);
		tmp = tmp->next;
	}
	return (cmd);
}
