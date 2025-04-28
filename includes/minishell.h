/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikayel <mikayel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 17:06:58 by ggevorgi          #+#    #+#             */
/*   Updated: 2025/04/28 19:13:51 by mikayel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define PROGRAMM_ERROR 0
# define MALLOC_ERROR 1
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
void		    *safe_malloc(size_t bytes);
void		    free_ptr(void *ptr);
void		    setup_signals(void);
void		    ft_echo(char *msg, bool is_nl);
void		    ft_exit(int status);
void	        ft_lstadd_back_token(t_token **lst, t_token *new);
t_token	        *ft_lstnew_token(t_token_type type, char *value);
t_token         *tokenize(char *line, int i);
t_token_type	oper_type(const char *s, int *len);

int				ft_strcmp(const char *s1, const char *s2);
char			*ft_strndup(const char *s, size_t n);

#endif