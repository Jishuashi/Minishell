/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchartie <hchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 12:31:25 by louka             #+#    #+#             */
/*   Updated: 2026/04/24 16:37:21 by hchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

static void	count_tokens_more(const char *line, int *i, char *quote)
{
	while (line[*i] && (line[*i] != ' ' || *quote))
	{
		if ((line[*i] == '"' || line[*i] == '\'')
			&& (!*quote || *quote == line[*i]))
		{
			if (*quote == line[*i])
				*quote = 0;
			else
				*quote = line[*i];
		}
		(*i)++;
	}
}

static int	count_tokens(const char *line)
{
	int		count;
	int		i;
	char	quote;

	count = 0;
	i = 0;
	while (line[i])
	{
		while (line[i] && line[i] == ' ')
			i++;
		if (line[i])
		{
			count++;
			quote = 0;
			count_tokens_more(line, &i, &quote);
		}
	}
	return (count);
}

char	**token(char *line, t_env_table *env)
{
	char	**tokens;
	int		nb_de_token;

	if (!line)
		return (NULL);
	nb_de_token = count_tokens(line);
	tokens = ft_calloc(nb_de_token + 1, sizeof(char *));
	if (!tokens)
		return (NULL);
	split_token(tokens, line, env);
	return (tokens);
}

int	len_token(char	**tokens)
{
	int	res;

	res = 0;
	while (*tokens)
	{
		res++;
		tokens++;
	}
	return (res);
}
