/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggevorgi <sp1tak.gg@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 17:06:58 by ggevorgi          #+#    #+#             */
/*   Updated: 2025/05/06 20:03:55 by ggevorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define PROGRAMM_ERROR 0
# define MALLOC_ERROR 1
# define SYNTAX_ERROR 2
# define INVALID_ARGUMENT_ERROR 3

#ifndef PATH_MAX
# define PATH_MAX 1024
#endif

//hash table
#include "ht.h"

//library
# include "libft.h"

# include <stdbool.h>
# include <limits.h>

// Работа с памятью и строками
# include <stdlib.h>
# include <string.h>
# include <stddef.h>
# include <errno.h>

// Ввод-вывод
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>

// Работа с процессами и сигналами
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>

// Работа с файлами и директориями
# include <dirent.h>
# include <sys/stat.h>

// readline
# include <readline/readline.h>
# include <readline/history.h>

// termios и управление терминалом
# include <termios.h>
# include <termcap.h>
# include <curses.h>
# include <sys/ioctl.h>

typedef enum e_token_type {
    TOKEN_WORD,
    TOKEN_PIPE,          // |
    TOKEN_AND,           // &&
    TOKEN_OR,            // ||
    TOKEN_REDIR_IN,      // <
    TOKEN_REDIR_OUT,     // >
    TOKEN_REDIR_APPEND,  // >>
    TOKEN_HEREDOC,       // <<
    TOKEN_PAREN_LEFT,    // (
    TOKEN_PAREN_RIGHT,   // )
    TOKEN_EOF
} t_token_type;

typedef enum e_ast_node_type {
    AST_COMMAND,     // обычная команда: echo, ls и т.д.
    AST_PIPE,        // |
    AST_AND,         // &&
    AST_OR,          // ||
    AST_SUBSHELL     // ( ... )
} t_ast_node_type;

typedef enum e_redir_type {
    REDIR_IN,        // <
    REDIR_OUT,       // >
    REDIR_APPEND,    // >>
    REDIR_HEREDOC    // <<
} t_redir_type;


typedef struct s_redirection {
    t_redir_type type;      // тип редиректа
    char *target;           // имя файла или delimiter
} t_redirection;


typedef struct s_cmd {
    char *name;                 // имя команды, например "echo"
    char **args;               // массив аргументов: {"echo", "lox", NULL}
    t_redirection **redirections; // массив указателей на редиректы
    size_t redir_count;         // количество редиректов
} t_cmd;


typedef struct s_ast {
    t_ast_node_type type;

    // Только если type == AST_COMMAND
    t_cmd *cmd;

    // Только если type == AST_PIPE, AST_AND, AST_OR
    struct s_ast *left;
    struct s_ast *right;

    // Только если type == AST_SUBSHELL
    struct s_ast *subshell;
} t_ast;


typedef struct s_token {
    char            *value;
    t_token_type    type;
    struct s_token  *next;
} t_token;

typedef struct s_shell {
    t_ht    *env;
    char    *shell_name;
    char    last_status_code;
    char    *commands;
} t_shell;



int			    ft_pwd(void);
bool	        is_operator(char c);
bool            ft_isspace(char c);
char		    *read_prompt(void);
void		    throw_err(int err_type);
void syntax_error(const char *token);
void		    *safe_malloc(size_t bytes);
void		    free_ptr(void *ptr);
void		    setup_signals(void);
void		    ft_echo(char *msg, bool is_nl);
void		    ft_exit(int status);
void	        ft_lstadd_back_token(t_token **lst, t_token *new);
void            print_env(t_ht *env);
t_token	        *ft_lstnew_token(t_token_type type, char *value);
t_token         *tokenize(char *line, int i);
t_token_type	oper_type(const char *s, int *len);

void add_redirection(t_cmd *cmd, t_redir_type type, char *target);
t_cmd *new_cmd_node(char *name);
void add_arg(t_cmd *cmd, char *arg);
t_cmd *create_cmd_from_tokens(t_token *tokens);

int				ft_strcmp(const char *s1, const char *s2);
char			*ft_strndup(const char *s, size_t n);

#endif