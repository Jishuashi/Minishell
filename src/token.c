/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louka <louka@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 12:31:25 by louka             #+#    #+#             */
/*   Updated: 2026/04/18 21:53:05 by louka            ###   ########.fr       */
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

char	**token(char *line)
{
	char	**tokens;
	int		nb_de_token;

	if (!line)
		return (NULL);
	nb_de_token = count_tokens(line);
	tokens = ft_calloc(nb_de_token + 1, sizeof(char *));
	if (!tokens)
		return (NULL);
	split_token(tokens, line);
	printf("DEBUG    NB DE TOKEN : %d\n", nb_de_token);
	int	i;
	i = 0;
	while (i < nb_de_token)
	{
		printf("DEBUG    token[%d]: %s\n", i,
			(tokens[i] ? tokens[i] : "(null)"));
		i++;
	}
	return (tokens);
}
