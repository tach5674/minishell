/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzohraby <mzohraby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 12:06:11 by mikayel           #+#    #+#             */
/*   Updated: 2025/06/17 16:57:56 by mzohraby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_H
# define EXPANSION_H

# include "minishell.h"

bool	check_if_quotes(char *str, char *in_quotes, int i);
bool	expand_tilde(char **str, t_ht *env);
bool	expand_arguments(char **str, t_shell *shell, bool check);
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
void	print_error_expansions(char *str);
bool	split_arguments(t_cmd *cmd, int j);
bool	split_arguments_redir(char *str);
int		is_whitespace(char c);
bool	skip_quoted_string(const char **str);
int		count_words(const char *str);
void	skip_quoted_string_and_count(const char **str, size_t *len);
char	*get_next_word(const char **str);
int		expand_empty(t_cmd *cmd, int j, t_ht *env);

#endif
