/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikayel <mikayel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 17:17:01 by ggevorgi          #+#    #+#             */
/*   Updated: 2025/04/28 16:04:23 by mikayel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

const char *token_type_str(t_token_type type)
{
	switch (type)
	{
		case TOKEN_WORD: return "WORD";
		case TOKEN_PIPE: return "PIPE";
		case TOKEN_AND: return "AND";
		case TOKEN_OR: return "OR";
		case TOKEN_REDIR_IN: return "REDIR_IN";
		case TOKEN_REDIR_OUT: return "REDIR_OUT";
		case TOKEN_REDIR_APPEND: return "APPEND";
		case TOKEN_HEREDOC: return "HEREDOC";
		case TOKEN_PAREN_LEFT: return "PAREN_LEFT";
		case TOKEN_PAREN_RIGHT: return "PAREN_RIGHT";
		case TOKEN_EOF: return "EOF";
		default: return "UNKNOWN";
	}
}

void	print_tokens(t_token *list)
{
	while (list)
	{
		printf("Type: %-12s | Value: '%s'\n",
		token_type_str(list->type), list->value);
		list = list->next;
	}
}

void	execute_commands(char *line)
{
	t_token	*token_list;

	token_list = tokenize(line, 0);
	print_tokens(token_list);
}

int	main(int argc, char *argv[], char *envp[])
{
	char	*line;
	t_ht	*env_table;
	
	(void) argv;
	env_table = ht_init(envp);
	ht_print(env_table);
	if (argc > 1)
		throw_err(INVALID_ARGUMENT_ERROR);
	setup_signals();
	while (1)
	{
		line = read_prompt();
		if (!line)
		{
			ft_putstr_fd("exit\n", 1);
			break ;
		}
		if (*line)
		{
			add_history(line);
			execute_commands(line);
		}
		free(line);
	}
	rl_clear_history();
	return (0);
}
