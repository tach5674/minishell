/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ht_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzohraby <mzohraby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 14:56:15 by ggevorgi          #+#    #+#             */
/*   Updated: 2025/06/14 13:45:13 by mzohraby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ht_init_error(t_ht *ht, char *key, char *value)
{
	if (key)
		free(key);
	if (value)
		free(value);
	ht_free(ht);
	throw_err(MALLOC_ERROR);
}

static void	ht_init_add(t_ht *ht, char **envp, int i)
{
	char	*equal;
	char	*key;
	char	*value;
	size_t	key_len;

	key = NULL;
	value = NULL;
	equal = ft_strchr(envp[i], '=');
	if (equal)
	{
		key_len = equal - envp[i];
		key = ft_strndup(envp[i], key_len);
		if (!key)
			ht_init_error(ht, key, value);
		value = ft_strdup(equal + 1);
		if (!value)
			ht_init_error(ht, key, value);
		if (ht_add(ht, key, value) == false)
			ht_init_error(ht, key, value);
		free(key);
		free(value);
	}
}

static void	ht_init_path(t_ht *ht)
{
	char	*temp;

	temp = ft_strjoin("PATH=", ht_get(ht, "PATH"));
	if (!temp)
	{
		if (errno)
		{
			ht_free(ht);
			throw_err(MALLOC_ERROR);
		}
		if (!ht_add(ht, "_", ""))
		{
			ht_free(ht);
			throw_err(MALLOC_ERROR);
		}
		return ;
	}
	if (!ht_add(ht, "_", temp))
	{
		ht_free(ht);
		free(temp);
		throw_err(MALLOC_ERROR);
	}
	free(temp);
}

static void	ht_init_shlvl(t_ht *ht)
{
	char	*value;

	if (ht_get(ht, "SHLVL"))
	{
		value = ft_itoa(ft_atoi(ht_get(ht, "SHLVL")) + 1);
		if (!value)
		{
			ht_free(ht);
			throw_err(MALLOC_ERROR);
		}
		if (!ht_add(ht, "SHLVL", value))
		{
			ht_free(ht);
			free(value);
			throw_err(MALLOC_ERROR);
		}
		free(value);
	}
	else if (!ht_add(ht, "SHLVL", "1"))
	{
		ht_free(ht);
		throw_err(MALLOC_ERROR);
	}
}

static void	ht_init_pwd(t_ht *ht)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, sizeof(cwd)) == NULL)
		throw_err(0);
	if (!ht_add(ht, "PWD", cwd))
	{
		ht_free(ht);
		throw_err(MALLOC_ERROR);
	}
}

t_ht	*ht_init(char **envp)
{
	t_ht	*ht;
	int		i;

	ht = malloc(sizeof(t_ht));
	if (!ht)
		throw_err(MALLOC_ERROR);
	ht->size = INITIAL_SIZE;
	ht->count = 0;
	ht->buckets = ft_calloc(ht->size, sizeof(t_ht_item *));
	if (!ht->buckets)
	{
		ht_free(ht);
		throw_err(MALLOC_ERROR);
	}
	if (envp)
	{
		i = 0;
		while (envp[i])
			ht_init_add(ht, envp, i++);
	}
	ht_init_path(ht);
	ht_init_shlvl(ht);
	ht_init_pwd(ht);
	return (ht);
}
