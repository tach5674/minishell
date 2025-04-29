/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikayel <mikayel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 17:17:01 by ggevorgi          #+#    #+#             */
/*   Updated: 2025/04/28 19:32:11 by mikayel          ###   ########.fr       */
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

void	shell_init(t_shell **shell, char **envp)
{
	(*shell)->env = ht_init(envp);
	(*shell)->last_status_code = '0';
	(*shell)->shell_name = "minishell";
}

int	main(int argc, char *argv[], char *envp[])
{
	t_shell	*shell;
	
	(void) argv;
	shell_init(&shell, envp);
	// ht_print(shell->env);
	if (argc > 1)
		throw_err(INVALID_ARGUMENT_ERROR);
	setup_signals();
	while (1)
	{
		shell->commands = read_prompt();
		if (!shell->commands)
		{
			ft_putstr_fd("exit\n", 1);
			break ;
		}
		if (*shell->commands)
		{
			add_history(shell->commands);
			execute_commands(shell->commands);
		}
		free(shell->commands);
	}
	rl_clear_history();
	return (0);
}
