/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikayel <mikayel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 19:04:37 by ggevorgi          #+#    #+#             */
/*   Updated: 2025/06/13 20:38:29 by mikayel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_redirect(t_token **tmp, t_cmd *cmd, t_redir_type type,
		t_shell *shell)
{
	t_token			*next;
	t_redirection	*redir;

	(void)shell;
	next = (*tmp)->next;
	if (!next || next->type != TOKEN_WORD)
	{
		if (next)
			syntax_error(next->value);
		else
			syntax_error("newline");
		if (shell->last_status_code)
			free(shell->last_status_code);
		shell->last_status_code = ft_itoa(2);
		if (!shell->last_status_code)
			perror("minishell");
		return (1);
	}
	redir = create_redirection(type, next->value, cmd->shell);
	if (!redir)
		return (2);
	add_redirection(cmd, redir);
	*tmp = next;
	return (0);
}

static void	handle_word_token(t_cmd *cmd, t_token *token)
{
	if (!cmd->name)
		cmd->name = ft_strdup(token->value);
	add_arg(cmd, token->value);
}

t_cmd	*create_cmd_from_tokens(t_token *tokens, t_shell *shell)
{
	t_cmd	*cmd;
	t_token	*tmp;

	tmp = tokens;
	cmd = new_cmd_node(NULL, shell);
	while (tmp && tmp->type != TOKEN_PIPE && tmp->type != TOKEN_AND
		&& tmp->type != TOKEN_OR && tmp->type != TOKEN_PAREN_RIGHT)
	{
		if (tmp->type == TOKEN_WORD)
			handle_word_token(cmd, tmp);
		else if (tmp->type == TOKEN_REDIR_IN && handle_redirect(&tmp, cmd,
				REDIR_IN, shell))
			return (free_cmd(cmd), NULL);
		else if (tmp->type == TOKEN_REDIR_OUT && handle_redirect(&tmp, cmd,
				REDIR_OUT, shell))
			return (free_cmd(cmd), NULL);
		else if (tmp->type == TOKEN_REDIR_APPEND && handle_redirect(&tmp, cmd,
				REDIR_APPEND, shell))
			return (free_cmd(cmd), NULL);
		else if (tmp->type == TOKEN_HEREDOC && handle_redirect(&tmp, cmd,
				REDIR_HEREDOC, shell))
			return (free_cmd(cmd), NULL);
		tmp = tmp->next;
	}
	return (cmd);
}
