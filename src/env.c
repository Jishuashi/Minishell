/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchartie <hchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 13:58:13 by hchartie          #+#    #+#             */
/*   Updated: 2026/05/27 15:54:31 by hchartie         ###   ########.fr       */
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

t_env_table	*empty_env(void)
{
	t_env_table	*res;
	char		buff[1024];

	res = (t_env_table *)malloc(sizeof(t_env_table));
	if (!res)
		return (NULL);
	res->size = 3;
	res->table = (t_env *)malloc(sizeof(t_env) * res->size);
	if (!res->table)
		return (free(res), NULL);
	res->table[0].name = ft_strdup("PWD");
	getcwd(buff, 1024);
	res->table[0].value = ft_strdup(buff);
	res->table[1].name = ft_strdup("SHLVL");
	res->table[1].value = ft_strdup("1");
	res->table[2].name = ft_strdup("_");
	res->table[2].value = ft_strdup("/usr/bin/env");
	return (res);
}

t_env_table	*create_env(char *envp[])
{
	t_env_table	*res;
	size_t		len;
	size_t		i;

	if (!envp[0])
		return (empty_env());
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
			return (free(res), NULL);
		i++;
	}
	return (res);
}

char	*get_env_value(char	*key, t_env_table *env)
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

void	set_env_value(char *key, char *value, t_env_table *env)
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
