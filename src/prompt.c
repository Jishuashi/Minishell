/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louka <louka@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 12:09:53 by louka             #+#    #+#             */
/*   Updated: 2026/04/16 12:29:14 by louka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

const char	*get_prompt(void)
{
	return ("minishell> ");
}

int	launch_minishell(void)
{
	char	*line;

	while (1)
	{
		line = readline(get_prompt());
		if (!line)
			break ;
		if (line[0] != '\0')
			add_history(line);
		free(line);
	}
	return (0);
}
