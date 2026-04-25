/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calloc_extend.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchartie <hchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 12:00:44 by louka             #+#    #+#             */
/*   Updated: 2026/04/25 18:02:09 by hchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "includes/minishell.h"

int	calloc_all(char ***var, int **i)
{
	*i = ft_calloc(2, sizeof(int));
	*var = ft_calloc(4, sizeof(char *));
	if (!*i || !*var)
	{
		free(*i);
		free(*var);
		return (0);
	}
	(*var)[3] = ft_calloc(2048, sizeof(char));
	if (!(*var)[3])
	{
		free(*i);
		free(*var);
		return (0);
	}
	return (1);
}
