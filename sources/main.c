/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggevorgi <sp1tak.gg@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 17:17:01 by ggevorgi          #+#    #+#             */
/*   Updated: 2025/05/06 20:17:56 by ggevorgi         ###   ########.fr       */
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
#include <stdio.h>

void print_cmd(t_cmd *cmd) {
    if (!cmd) {
        printf("Command: NULL\n");
        return;
    }

    printf("Command name: %s\n", cmd->name ? cmd->name : "NULL");

    printf("Arguments:\n");
    if (cmd->args) {
        for (size_t i = 0; cmd->args[i]; i++) {
            printf("  [%zu]: %s\n", i, cmd->args[i]);
        }
    } else {
        printf("  None\n");
    }

    printf("Redirections:\n");
    if (cmd->redirections && cmd->redir_count > 0) {
        for (size_t i = 0; i < cmd->redir_count; i++) {
            t_redirection *r = cmd->redirections[i];
            if (!r) continue;
            const char *type_str = "UNKNOWN";
            switch (r->type) {
                case REDIR_IN: type_str = "<"; break;
                case REDIR_OUT: type_str = ">"; break;
                case REDIR_APPEND: type_str = ">>"; break;
                case REDIR_HEREDOC: type_str = "<<"; break;
            }
            printf("  [%zu]: %s %s\n", i, type_str, r->target ? r->target : "NULL");
        }
    } else {
        printf("  None\n");
    }
}

void	execute_commands(t_shell *shell_data)
{
	t_token	*token_list;

	token_list = tokenize(shell_data->commands, 0);
	t_cmd *cmd = create_cmd_from_tokens(token_list);
	if (cmd)
		print_cmd(cmd);
	// print_tokens(token_list);
}

void	shell_init(t_shell **shell, char **envp)
{
(void) envp;
	// (*shell)->env = ht_init(envp);
	(*shell)->last_status_code = '0';
	(*shell)->shell_name = "minishell";
}

int	main(int argc, char *argv[], char *envp[])
{
	t_shell	*shell;

	(void) argv;
	shell = safe_malloc(sizeof(t_shell));
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
			execute_commands(shell);
		}
		free(shell->commands);
	}
	rl_clear_history();
	return (0);
}
