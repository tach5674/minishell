/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggevorgi <sp1tak.gg@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 17:17:01 by ggevorgi          #+#    #+#             */
/*   Updated: 2025/05/20 20:04:53 by ggevorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_ast_node(t_ast *node, int depth)
{
	if (!node)
		return;

	// Отступы для визуальной структуры дерева
	for (int i = 0; i < depth; i++)
		printf("  ");

	// Печать типа узла
	if (node->type == AST_COMMAND)
	{
		printf("AST_COMMAND\n");
		printf("%*sCommand: %s\n", depth * 2, "", node->cmd->name);
		for (size_t i = 0; i < node->cmd->redir_count; i++)
		{
			printf("%*sRedirection %zu: %s %s\n", depth * 2, "", i + 1, 
				node->cmd->redirections[i]->type == REDIR_IN ? "<" :
				node->cmd->redirections[i]->type == REDIR_OUT ? ">" :
				node->cmd->redirections[i]->type == REDIR_APPEND ? ">>" : "<<", 
				node->cmd->redirections[i]->target);
		}
	}
	else if (node->type == AST_PIPE)
	{
		printf("AST_PIPE\n");
	}
	else if (node->type == AST_AND)
	{
		printf("AST_AND\n");
	}
	else if (node->type == AST_OR)
	{
		printf("AST_OR\n");
	}
	else if (node->type == AST_SUBSHELL)
	{
		printf("AST_SUBSHELL\n");
	}

	// Рекурсивный вызов для левого и правого поддеревьев
	if (node->left)
		print_ast_node(node->left, depth + 1);
	if (node->right)
		print_ast_node(node->right, depth + 1);
	if (node->subshell)
		print_ast_node(node->subshell, depth + 1);
}

void	print_ast(t_ast *ast)
{
	if (!ast)
	{
		printf("AST is NULL\n");
		return;
	}
	print_ast_node(ast, 0);
}

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
	t_ast	*ast;
	t_token	*tokens;
	t_token	*tokens_tmp;

	tokens = tokenize(shell_data->commands, 0);
	tokens_tmp = tokens;
	// print_tokens(tokens);
	ast = parse(&tokens);
	free_tokens(tokens_tmp);
	print_ast(ast);
	free_ast(ast);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_shell	*shell;

	shell = safe_malloc(sizeof(t_shell));
	shell_init(shell, envp);
	if (argc > 1 && argv)
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
	free_shell(shell);
	return (0);
}
