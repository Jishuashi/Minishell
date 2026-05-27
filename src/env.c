/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchartie <hchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 13:58:13 by hchartie          #+#    #+#             */
/*   Updated: 2026/05/27 12:10:04 by hchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/env.h"
#include "./includes/minishell.h"

static int	fill_env(t_env *entry, char *env_line)
{
	char	*equal;

	equal = ft_strchr(env_line, '=');
	if (equal)
	{
		entry->name = ft_substr(env_line, 0, equal - env_line);
		entry->value = ft_strdup(equal + 1);
	}
	else
	{
		entry->name = ft_strdup(env_line);
		entry->value = ft_strdup("");
	}
	return (entry->name && entry->value);
}

t_env_table	*create_env(char *envp[])
{
	t_env_table	*res;
	size_t		len;
	size_t		i;

	len = count_double_char(envp);
	res = (t_env_table *)malloc(sizeof(t_env_table));
	if (!res)
		return (NULL);
	res->table = (t_env *)malloc(sizeof(t_env) * len);
	if (!res->table)
		return (free(res), NULL);
	res->size = len;
	i = 0;
	while (i < len)
	{
		if (!fill_env(&res->table[i], envp[i]))
			return (NULL);
		i++;
	}
	return (res);
}

void	print_env(t_env_table *env)
{
	size_t	i;

	i = 0;
	while (i < env->size)
	{
		ft_printf("%s=", env->table[i].name);
		ft_printf("%s\n", env->table[i].value);
		i++;
	}
}

char	*get_value(char	*key, t_env_table *env)
{
	size_t	i;

	i = 0;
	while (i < env->size)
	{
		if (ft_strncmp(env->table[i].name, key, ft_strlen(key) + 1) == 0)
			return (env->table[i].value);
		i++;
	}
	return (NULL);
}

void	set_env_var(char *key, char *value, t_env_table *env)
{
	size_t	i;
	char	*new_val;

	i = 0;
	while (i < env->size)
	{
		if (ft_strncmp(env->table[i].name, key, ft_strlen(key) + 1) == 0)
		{
			new_val = ft_strdup(value);
			if (new_val)
			{
				free(env->table[i].value);
				env->table[i].value = new_val;
			}
			return ;
		}
		i++;
	}
}
