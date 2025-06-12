/* ************************************************************************** */
/*																			  */
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

# include "structs.h"
# include "shell.h"
# include "utils.h"
# include "signals.h"
# include "tokenisation.h"
# include "heredoc.h"
# include "parsing.h"
# include "ast.h"
# include "built_in.h"
# include "execution.h"
# include "expansion.h"
# include "ht.h"

extern int		g_signal_status;

#endif