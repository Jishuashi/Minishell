/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchartie <hchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 14:09:17 by hchartie          #+#    #+#             */
/*   Updated: 2026/05/30 15:37:35 by hchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

size_t	count_double_char(char **tab)
{
	size_t	res;

	res = 0;
	while (*tab)
	{
		res++;
		tab++;
	}
	return (res);
}

void	ft_free_all(char **pfree)
{
	char	**start;

	if (!pfree)
		return ;
	start = pfree;
	while (*pfree)
	{
		free(*pfree);
		pfree++;
	}
	free(start);
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

char *extend_tilde(char *path, char *home)
{
	size_t	i;
	char 	*temp;

	if (!path)
		return (NULL);
	if (path[0] != '~')
		return (path);
	i = 0;
	while (i < ft_strlen(path))
	{
		path[i] = path[i + 1];
		i++;
	}
	temp = path;
	path = ft_strjoin(home, path);
	free(temp);
	return (path);
}