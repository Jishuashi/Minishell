/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchartie <hchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 14:09:17 by hchartie          #+#    #+#             */
/*   Updated: 2026/05/27 15:35:04 by hchartie         ###   ########.fr       */
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
