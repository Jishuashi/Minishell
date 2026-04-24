/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louka <louka@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 21:45:48 by louka             #+#    #+#             */
/*   Updated: 2026/04/24 13:24:43 by louka            ###   ########.fr       */
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
		}
		len++;
		i++;
	}
	return (len);
}

static char	copy_token(char *dst, char *line, int *i)
{
	int		k;
	char	*quote;

	k = 0;
	quote = calloc(1, 2);
	quote[0] = 0;
	quote[1] = 0;
	while (line[*i] && (line[*i] != ' ' || quote[0]))
	{
		quote[1] = 0;
		if (is_quote(line[*i]) && (!quote[0] || quote[0] == line[*i]))
		{
			quote[0] = toggle_quote(quote[0], line[*i]);
			if (quote[0] == '\'')
				quote[1] = '\'';
			(*i)++;
		}
		if (quote[0] == '\'' && line[*i] == '$')
		{
			dst[k++] = 31;
			(*i)++;
		}
		dst[k++] = line[(*i)++];
	}
	return (dst[k] = '\0', quote[1]);
}

char	**split_token(char **token, char *line, t_env_table *env)
{
	int	i;
	int	j;

	(void)env;
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
		token[j] = extend(token[j], env);
		j++;
	}
	token[j] = NULL;
	return (token);
}
