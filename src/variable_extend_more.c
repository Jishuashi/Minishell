/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_extend_more.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louka <louka@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 17:40:38 by ldeplace          #+#    #+#             */
/*   Updated: 2026/04/27 18:09:38 by louka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	calloc_all(char ***var, int **i)
{
	*i = ft_calloc(3, sizeof(int));
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

void	if_token(int last_status, int *i, char **var)
{
	char	*status;

	status = ft_itoa(last_status);
	if (status)
	{
		i[1] += ft_strlcpy(var[3] + i[1], status, 2048 - i[1]);
		free(status);
	}
	i[0] += 2;
}
