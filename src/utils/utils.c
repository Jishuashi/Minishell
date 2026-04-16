/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchartie <hchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 14:09:17 by hchartie          #+#    #+#             */
/*   Updated: 2026/04/16 15:54:25 by hchartie         ###   ########.fr       */
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
	while (*pfree)
	{
		free(*pfree);
		pfree++;
	}
	free(pfree);
}
