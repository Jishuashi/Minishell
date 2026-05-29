/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_more.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louka2b <louka2b@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 13:55:33 by louka2b           #+#    #+#             */
/*   Updated: 2026/05/29 16:53:52 by louka2b          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdlib.h>

static void	bubble_sort_env(t_env *table, size_t size)
{
	size_t	i;
	size_t	j;
	t_env	tmp;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j + 1 < size - i)
		{
			if (ft_strncmp(table[j].name, table[j + 1].name,
					ft_strlen(table[j].name) + 1) > 0)
			{
				tmp = table[j];
				table[j] = table[j + 1];
				table[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
}

static void	print_export_env(t_env_table *env)
{
	t_env	*sorted;
	size_t	i;

	sorted = (t_env *)malloc(sizeof(t_env) * env->size);
	if (!sorted)
		return ;
	i = 0;
	while (i < env->size)
	{
		sorted[i] = env->table[i];
		i++;
	}
	bubble_sort_env(sorted, env->size);
	i = 0;
	while (i < env->size)
	{
		printf("declare -x %s", sorted[i].name);
		if (sorted[i].value && sorted[i].value[0])
			printf("=\"%s\"", sorted[i].value);
		printf("\n");
		i++;
	}
	free(sorted);
}

void	exit_shell(int status, t_env_table *env)
{
	if (env)
		free_env(env);
	printf("exit\n");
	rl_clear_history();
	exit(status);
}

static void	export_one(char *arg, t_env_table *env)
{
	char	*equal;
	char	*key;
	char	*value;

	equal = ft_strchr(arg, '=');
	if (!equal)
	{
		set_env_value(arg, "", env);
		return ;
	}
	key = ft_substr(arg, 0, equal - arg);
	if (!key)
		return ;
	value = ft_strdup(equal + 1);
	if (!value)
	{
		free(key);
		return ;
	}
	set_env_value(key, value, env);
	free(key);
	free(value);
}

void	ft_export(char **cmd, t_env_table *env)
{
	int	i;

	if (cmd[1] == NULL)
	{
		print_export_env(env);
		return ;
	}
	i = 1;
	while (cmd[i])
	{
		export_one(cmd[i], env);
		i++;
	}
}
