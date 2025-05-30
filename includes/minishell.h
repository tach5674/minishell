/* ************************************************************************** */
/*									                                                */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggevorgi <sp1tak.gg@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 17:06:58 by ggevorgi          #+#    #+#             */
/*   Updated: 2025/05/13 16:55:00 by ggevorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define PROGRAMM_ERROR 0
# define MALLOC_ERROR 1
# define SYNTAX_ERROR 2
# define INVALID_ARGUMENT_ERROR 3

# ifndef PATH_MAX
#  define PATH_MAX 1024
# endif

// library
# include "libft.h"
# include <limits.h>
# include <stdbool.h>

// Работа с памятью и строками
# include <errno.h>
# include <stddef.h>
# include <stdlib.h>
# include <string.h>

// Ввод-вывод
# include <fcntl.h>
# include <stdio.h>
# include <unistd.h>

// Работа с процессами и сигналами
# include <signal.h>
# include <sys/types.h>
# include <sys/wait.h>

// Работа с файлами и директориями
# include <dirent.h>
# include <sys/stat.h>

// readline
# include <readline/history.h>
# include <readline/readline.h>

// termios и управление терминалом
# include <curses.h>
# include <sys/ioctl.h>
# include <termcap.h>
# include <termios.h>

// hash table
# include "ht.h"

extern int			signal_status;

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,         // |
	TOKEN_AND,          // &&
	TOKEN_OR,           // ||
	TOKEN_REDIR_IN,     // <
	TOKEN_REDIR_OUT,    // >
	TOKEN_REDIR_APPEND, // >>
	TOKEN_HEREDOC,      // <<
	TOKEN_PAREN_LEFT,   // (
	TOKEN_PAREN_RIGHT,  // )
	TOKEN_EOF
}					t_token_type;

typedef enum e_ast_node_type
{
	AST_COMMAND, // обычная команда: echo, ls и т.д.
	AST_PIPE,    // |
	AST_AND,     // &&
	AST_OR,      // ||
	AST_SUBSHELL // ( ... )
}					t_ast_node_type;

typedef enum e_redir_type
{
	REDIR_IN,     // <
	REDIR_OUT,    // >
	REDIR_APPEND, // >>
	REDIR_HEREDOC // <<
}					t_redir_type;

typedef struct s_redirection
{
	t_redir_type	type;
	char			*target;
	int				heredoc_fd;
}					t_redirection;

typedef struct s_cmd
{
	char			*name;
	char			**args;
	size_t			redir_count;
	t_redirection	**redirections;
	int				pipe_in;
	int				pipe_out;
	bool			in_subshell;
}					t_cmd;

typedef struct s_ast
{
	t_ast_node_type	type;
	t_cmd			*cmd;
	struct s_ast	*left;
	struct s_ast	*right;
	struct s_ast	*subshell;
}					t_ast;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
	struct s_token	*next;
}					t_token;

typedef struct s_shell
{
	char			**shell_envp;
	t_ht			*env;
	char			*shell_name;
	int				last_status_code;
	char			*commands;
	t_ast			*ast;
}					t_shell;

// execution
# include "execution.h"

void				setup_heredoc_signals(void);
bool				is_operator(char c);
bool				ft_isspace(char c);
t_token_type		oper_type(const char *s, int *len);
void				*safe_malloc(size_t bytes);
void				free_ptr(void *ptr);
void				free_shell(t_shell *shell);
void				free_cmd(t_cmd *cmd);
void				free_ast(t_ast *ast);
void				free_tokens(t_token *tokens);
void				throw_err(int err_type);
void				syntax_error(const char *token);

int					ft_pwd(t_cmd *cmd);
int					ft_echo(t_cmd *cmd);
int					ft_exit(t_cmd *cmd, t_shell *shell_data);
int					ft_env(t_cmd *cmd, t_ht *env);
int					handle_error(char *name);

void				cleanup_heredoc_files(t_cmd *cmd);
int					process_heredoc(const char *delimiter, char **out_filename);
void				setup_signals(void);
void				setup_signals_child(void);
void				setup_signals_parent_exec(void);
void				shell_init(t_shell *shell, char **envp);
t_ast				*parse(t_token **tokens);
t_ast				*parse_subshell(t_token **tokens);
t_ast				*parse_and_or(t_token **tokens);
t_ast				*parse_command_or_subshell(t_token **tokens);
t_ast				*parse_pipeline(t_token **tokens);
t_cmd				*create_cmd_from_tokens(t_token *tokens);
t_ast				*new_ast_node(t_ast_node_type type);
t_cmd				*new_cmd_node(char *name);
void				add_redirection(t_cmd *cmd, t_redirection *redir);
t_redirection		*create_redirection(t_redir_type type, const char *target);
void				add_arg(t_cmd *cmd, char *arg);
t_token				*tokenize(char *line, int i);
t_token				*ft_lstnew_token(t_token_type type, char *value);
void				ft_lstadd_back_token(t_token **lst, t_token *new);
char				*read_prompt(void);
int					ft_strcmp(const char *s1, const char *s2);
char				*ft_strndup(const char *s, size_t n);

#endif