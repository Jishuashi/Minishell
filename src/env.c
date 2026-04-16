/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchartie <hchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 13:58:13 by hchartie          #+#    #+#             */
/*   Updated: 2026/04/16 16:05:33 by hchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/env.h"
#include "./includes/minishell.h"

t_env_table	*create_env(char *envp[])
{
	t_env_table	*res;
	size_t		len;
	size_t		i;
	t_env		current;
	char		**splited;

	len = count_double_char(envp);
	res = (t_env_table *)malloc(sizeof(t_env_table));
	res->table = (t_env *)malloc(sizeof(t_env) * len);
	res->size = len;
	i = 0;
	while (i < len)
	{
		splited = ft_split(envp[i], '=');
		current.name = splited[0];
		current.value = splited[1];
		res->table[i] = current;
		free(splited);
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
		if (ft_strncmp(env->table->name, key, ft_strlen(key)) == 0)
			return (env->table[i].value);
		i++;
	}
	return (NULL);
}
