/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikayel <mikayel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 12:06:11 by mikayel           #+#    #+#             */
/*   Updated: 2025/06/10 12:58:29 by mikayel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_H
# define EXPANSION_H

# include "minishell.h"

bool	check_if_quotes(char *str, int *in_quotes, int i);
bool	expand_tilde(char **str, t_ht *env);
bool	expand_arguments(char **str, t_shell *shell);
bool    apply_expansions(char **args, t_shell *shell);

#endif
