/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggevorgi <sp1tak.gg@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 17:06:58 by ggevorgi          #+#    #+#             */
/*   Updated: 2025/04/21 14:08:28 by ggevorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

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

void ft_print(char *str);


#endif