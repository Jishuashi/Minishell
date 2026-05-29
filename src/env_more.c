/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_more.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louka2b <louka2b@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 14:48:31 by louka2b           #+#    #+#             */
/*   Updated: 2026/05/29 14:51:02 by louka2b          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

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

void	increment_shlvl(t_env_table *env)
{
	size_t	i;
	int		level;
	char	*new_level;

	i = 0;
	while (i < env->size)
	{
		if (ft_strncmp(env->table[i].name, "SHLVL", 6) == 0)
		{
			level = ft_atoi(env->table[i].value);
			new_level = ft_itoa(level + 1);
			if (new_level)
			{
				free(env->table[i].value);
				env->table[i].value = new_level;
			}
			return ;
		}
		i++;
	}
}
