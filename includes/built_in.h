/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzohraby <mzohraby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 13:28:11 by mzohraby          #+#    #+#             */
/*   Updated: 2025/06/17 12:27:33 by mzohraby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILT_IN_H
# define BUILT_IN_H

# include "minishell.h"

# ifndef PATH_MAX
#  define PATH_MAX 1024
# endif

int		ft_echo(t_cmd *cmd);
int		ft_exit(t_cmd *cmd, t_shell *shell_data);
int		ft_env(t_cmd *cmd, t_ht *env);
int		ft_pwd(t_cmd *cmd, t_ht *env);
int		ft_cd(t_cmd *cmd, t_ht *env);
int		ft_export(t_cmd *cmd, t_ht *env);
int		add_no_value(t_ht *env, char **args, t_export_state *state);
int		ft_unset(t_cmd *cmd, t_ht *env);
int		handle_error(char *name);
void	print_error_export(t_cmd *cmd, t_export_state *state);
int		ht_print_export_default(t_ht *ht);

#endif