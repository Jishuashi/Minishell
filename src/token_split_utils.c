/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_split_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louka <louka@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 17:30:00 by louka             #+#    #+#             */
/*   Updated: 2026/06/02 17:30:00 by louka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	has_quote(char *token)
{
	int	i;

	i = 0;
	while (token[i])
	{
		if (token[i] == '"' || token[i] == '\'')
			return (1);
		i++;
	}
	return (0);
}

char	*mark_quoted(char *expanded)
{
	char	*marked;

	marked = ft_calloc(ft_strlen(expanded) + 2, sizeof(char));
	if (!marked)
	{
		free(expanded);
		return (NULL);
	}
	marked[0] = '\1';
	ft_strlcpy(marked + 1, expanded, ft_strlen(expanded) + 1);
	free(expanded);
	return (marked);
}
