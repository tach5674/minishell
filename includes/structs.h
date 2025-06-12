/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzohraby <mzohraby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 13:05:38 by mzohraby          #+#    #+#             */
/*   Updated: 2025/06/12 18:58:30 by mzohraby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "minishell.h"

// Tokenisation

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_AND,
	TOKEN_OR,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_REDIR_APPEND,
	TOKEN_HEREDOC,
	TOKEN_PAREN_LEFT,
	TOKEN_PAREN_RIGHT,
	TOKEN_EOF
}						t_token_type;

// Hash table

typedef struct s_ht_item
{
	char				*key;
	char				*value;
	struct s_ht_item	*next;
}						t_ht_item;

typedef struct s_ht
{
	t_ht_item			**buckets;
	size_t				size;
	size_t				count;
}						t_ht;

// AST

typedef enum e_redir_type
{
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	REDIR_HEREDOC
}						t_redir_type;

typedef struct s_redirection
{
	t_redir_type		type;
	char				*target;
	int					heredoc_fd;
}						t_redirection;

typedef struct s_cmd
{
	char				*name;
	char				**args;
	size_t				redir_count;
	t_redirection		**redirections;
	int					pipe_in;
	int					pipe_out;
	struct s_shell		*shell;
	bool				in_subshell;
}						t_cmd;

typedef enum e_ast_node_type
{
	AST_COMMAND,
	AST_PIPE,
	AST_AND,
	AST_OR,
	AST_SUBSHELL
}						t_ast_node_type;

typedef struct s_ast
{
	t_ast_node_type		type;
	t_cmd				*cmd;
	struct s_ast		*left;
	struct s_ast		*right;
	struct s_ast		*subshell;
}						t_ast;

typedef struct s_token
{
	char				*value;
	t_token_type		type;
	struct s_token		*next;
}						t_token;

typedef struct s_heredoc
{
	char				*filename;
	struct s_heredoc	*next;
}						t_heredoc;

// Shell

typedef struct s_shell
{
	struct termios		original_termios;
	t_ht				*env;
	char				**shell_envp;
	char				*shell_name;
	char				*last_status_code;
	char				*commands;
	t_heredoc			*heredocs;
	t_ast				*ast;
}						t_shell;

// Wildcards

typedef struct s_match_state
{
	const char			*p;
	const char			*s;
	const char			*star;
	const char			*ss;
	char				quote;
}						t_match_state;

typedef struct s_expand_state
{
	const char			*pattern;
	bool				show_hidden;
	bool				only_dir;
	int					*count;
	char				***match_list;
	int					*capacity;
}						t_expand_state;

#endif