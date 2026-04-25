/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchartie <hchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 15:23:11 by hchartie          #+#    #+#             */
/*   Updated: 2026/04/25 04:59:45 by hchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

static int	count_cmd(char **tokens);

t_args	*parse_args(char **tokens)
{
	t_args	*args;

	args = NULL;
	printf("NB Cmd: %d\n", count_cmd(tokens));
	return (args);
}

static int	count_cmd(char **tokens)
{
	int	i;
	int	res;
	int	len;

	i = 0;
	res = 0;
	len = len_token(tokens);
	while (i < len)
	{
		if (tokens[i][0] == '<' || tokens[i][0] == '>')
			i += 2;
		else if (tokens[i][0] == '|')
			i++;
		else
		{
			res++;
			i++;
		}
	}
	return (res);
}
