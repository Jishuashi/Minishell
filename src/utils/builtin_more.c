/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_more.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louka <louka@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 13:55:33 by louka2b           #+#    #+#             */
/*   Updated: 2026/06/02 17:25:44 by louka            ###   ########.fr       */
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
		ft_printf("declare -x %s", sorted[i].name);
		if (sorted[i].value && sorted[i].value[0])
			ft_printf("=\"%s\"", sorted[i].value);
		ft_printf("\n");
		i++;
	}
	free(sorted);
}

void	exit_shell(int status, t_env_table *env)
{
	if (env)
		free_env(env);
	ft_printf("exit\n");
	rl_clear_history();
	exit(status);
}

static int	export_one(char *arg, t_env_table *env)
{
	int		i;
	char	*equal;
	char	*key;
	char	*value;

	if (!arg || !arg[0] || (!ft_isalpha(arg[0]) && arg[0] != '_'))
	{
		ft_putstr_fd("minishell: export: ", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd(": not a valid identifier\n", 2);
		return (1);
	}
	i = 1;
	while (arg[i] && arg[i] != '=')
	{
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
		{
			ft_putstr_fd("minishell: export: ", 2);
			ft_putstr_fd(arg, 2);
			ft_putstr_fd(": not a valid identifier\n", 2);
			return (1);
		}
		i++;
	}
	equal = ft_strchr(arg, '=');
	if (!equal)
	{
		set_env_value(arg, "", env);
		return (0);
	}
	key = ft_substr(arg, 0, equal - arg);
	if (!key)
		return (1);
	value = ft_strdup(equal + 1);
	if (!value)
	{
		free(key);
		return (1);
	}
	set_env_value(key, value, env);
	free(key);
	free(value);
	return (0);
}

int	ft_export(char **cmd, t_env_table *env)
{
	int	i;
	int	ret;

	if (cmd[1] == NULL)
	{
		print_export_env(env);
		return (0);
	}
	ret = 0;
	i = 1;
	while (cmd[i])
	{
		if (export_one(cmd[i], env) != 0)
			ret = 1;
		i++;
	}
	return (ret);
}
