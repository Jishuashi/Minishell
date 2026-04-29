/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_extend_more.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louka <louka@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 17:40:38 by ldeplace          #+#    #+#             */
/*   Updated: 2026/04/29 14:25:23 by louka            ###   ########.fr       */
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

void	ft_check_quote(t_extend *all)
{
	if (all->token[all->i[0]] == '\'' && !all->in_double_quote)
	{
		all->in_single_quote = !all->in_single_quote;
		all->i[0]++;
		return ;
	}
	if (all->token[all->i[0]] == '"' && !all->in_single_quote)
	{
		all->in_double_quote = !all->in_double_quote;
		all->i[0]++;
		return ;
	}
	if (all->token[all->i[0]] == '$' && !all->in_single_quote)
		need_extend(all->var, all->env, all->i, all->token);
	else
		append_char(all->var[3], &all->i[1], all->token[all->i[0]++]);
}
