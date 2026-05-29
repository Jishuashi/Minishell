/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_more.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louka2b <louka2b@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 14:48:31 by louka2b           #+#    #+#             */
/*   Updated: 2026/05/29 16:41:24 by louka2b          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

static size_t	find_env_index(char *key, t_env_table *env)
{
	size_t	i;

	i = 0;
	while (i < env->size)
	{
		if (ft_strncmp(env->table[i].name, key, ft_strlen(key) + 1) == 0)
			return (i);
		i++;
	}
	return (env->size);
}

static t_env	*clone_env_without(t_env_table *env, size_t skip)
{
	t_env	*new_table;
	size_t	index;
	size_t	j;

	new_table = (t_env *)malloc(sizeof(t_env) * (env->size - 1));
	if (!new_table)
		return (NULL);
	index = 0;
	j = 0;
	while (index < env->size)
	{
		if (index != skip)
		{
			new_table[j] = env->table[index];
			j++;
		}
		index++;
	}
	return (new_table);
}

void	add_env_value(char *key, char *value, t_env_table *env)
{
	t_env	*new_table;
	size_t	i;

	new_table = (t_env *)malloc(sizeof(t_env) * (env->size + 1));
	if (!new_table)
		return ;
	i = 0;
	while (i < env->size)
	{
		new_table[i] = env->table[i];
		i++;
	}
	new_table[i].name = ft_strdup(key);
	new_table[i].value = ft_strdup(value);
	if (!new_table[i].name || !new_table[i].value)
	{
		free(new_table[i].name);
		free(new_table[i].value);
		free(new_table);
		return ;
	}
	free(env->table);
	env->table = new_table;
	env->size++;
}

void	remove_env_value(char *key, t_env_table *env)
{
	t_env	*new_table;
	size_t	i;

	i = find_env_index(key, env);
	if (i == env->size)
		return ;
	free(env->table[i].name);
	free(env->table[i].value);
	if (env->size == 1)
	{
		free(env->table);
		env->table = NULL;
		env->size = 0;
		return ;
	}
	new_table = clone_env_without(env, i);
	if (!new_table)
		return ;
	free(env->table);
	env->table = new_table;
	env->size--;
}

void	increment_shlvl(t_env_table *env)
{
	size_t	i;
	int		tmp;
	char	*new_tmp;

	i = 0;
	while (i < env->size)
	{
		if (ft_strncmp(env->table[i].name, "SHLVL", 6) == 0)
		{
			tmp = ft_atoi(env->table[i].value);
			new_tmp = ft_itoa(tmp + 1);
			if (new_tmp)
			{
				free(env->table[i].value);
				env->table[i].value = new_tmp;
			}
			return ;
		}
		i++;
	}
}
