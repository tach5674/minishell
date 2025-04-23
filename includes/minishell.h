/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggevorgi <sp1tak.gg@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 17:06:58 by ggevorgi          #+#    #+#             */
/*   Updated: 2025/04/23 15:18:04 by ggevorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define PROGRAMM_ERROR 0
# define MALLOC_ERROR 1
# define INVALID_ARGUMENT_ERROR 3

//library
# include "libft.h"

#include <stdbool.h>

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
# include <curses.h> // нужен для tgetent и других termcap-функций
# include <sys/ioctl.h>

void	throw_err(int err_type);
void	*safe_malloc(size_t bytes);
void	free_ptr(void *ptr);
char	*read_promt(void);
void	setup_signals(void);


#endif