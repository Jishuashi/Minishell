/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louka <louka@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 21:45:48 by louka             #+#    #+#             */
/*   Updated: 2026/04/18 21:51:49 by louka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

static int	is_quote(char c)
{
	return (c == '"' || c == '\'');
}

static char	toggle_quote(char quote, char c)
{
	if (quote == c)
		return (0);
	return (c);
}

static int	token_len(const char *line, int i)
{
	int		len;
	char	quote;

	len = 0;
	quote = 0;
	while (line[i] && (line[i] != ' ' || quote))
	{
		if (is_quote(line[i]) && (!quote || quote == line[i]))
		{
			quote = toggle_quote(quote, line[i]);
			i++;
			continue ;
		}
		len++;
		i++;
	}
	return (len);
}

static void	copy_token(char *dst, char *line, int *i)
{
	int		k;
	char	quote;

	k = 0;
	quote = 0;
	while (line[*i] && (line[*i] != ' ' || quote))
	{
		if (is_quote(line[*i]) && (!quote || quote == line[*i]))
		{
			quote = toggle_quote(quote, line[*i]);
			(*i)++;
			continue ;
		}
		dst[k++] = line[(*i)++];
	}
	dst[k] = '\0';
}

char	**split_token(char **token, char *line)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (line[i])
	{
		while (line[i] && line[i] == ' ')
			i++;
		if (!line[i])
			break ;
		token[j] = ft_calloc(token_len(line, i) + 1, sizeof(char));
		if (!token[j])
			return (NULL);
		copy_token(token[j], line, &i);
		j++;
	}
	token[j] = NULL;
	return (token);
}
