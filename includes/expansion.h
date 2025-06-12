/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzohraby <mzohraby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 12:06:11 by mikayel           #+#    #+#             */
/*   Updated: 2025/06/12 19:07:08 by mzohraby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_H
# define EXPANSION_H

# include "minishell.h"

bool	check_if_quotes(char *str, char *in_quotes, int i);
bool	expand_tilde(char **str, t_ht *env);
bool	expand_arguments(char **str, t_shell *shell);
char	**wildcard_expand(const char *pattern, int *count, bool show_hidden,
			bool only_dir);
bool	apply_expansions(t_cmd *cmd, t_shell *shell);

bool	remove_quotes(char **str);

bool	contains_wildcard(char *str);

bool	append_to_arguments(t_cmd *cmd, char **match_list, size_t i, int count);

bool	expand_wildcards(t_cmd *cmd, size_t *i);

bool	expand_wildcards_redir(char **str);

bool	resize_list(char ***list, int *capacity);

void	free_list(char **arr, int n);

int		matches(const char *p, const char *s);

#endif
