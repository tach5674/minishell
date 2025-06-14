/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggevorgi <sp1tak.gg@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 13:50:11 by mzohraby          #+#    #+#             */
/*   Updated: 2025/06/14 10:51:05 by ggevorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "minishell.h"

# define PROGRAMM_ERROR 0
# define MALLOC_ERROR 1
# define SYNTAX_ERROR 2
# define INVALID_ARGUMENT_ERROR 3

bool	ft_isspace(char c);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strndup(const char *s, size_t n);
char	*ft_str_char_join(char const *s1, char const *s2, char c);
void	free_split(char **arr);

void	throw_err(int err_type);
void	syntax_error(char *token);

void	free_ptr(void *ptr);
void	*safe_malloc(size_t bytes);
void	cleanup_heredocs(t_shell *shell);

void	sorter(char **match_list, int count);

#endif