/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_split_more.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louka <louka@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 14:35:58 by louka             #+#    #+#             */
/*   Updated: 2026/06/02 17:02:52 by louka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	is_quote(char c)
{
	return (c == '"' || c == '\'');
}

char	toggle_quote(char quote, char c)
{
	if (quote == c)
		return (0);
	return (c);
}

static void	update_quote(const char *line, char *quote, int i)
{
	if ((line[i] == '"' || line[i] == '\'') && (!*quote || *quote == line[i]))
	{
		if (*quote == line[i])
			*quote = 0;
		else
			*quote = line[i];
	}
}

static int	append_separator(char *res, const char *line, int *i, int *j)
{
	if (line[*i] == '<' || line[*i] == '>' || line[*i] == '|')
	{
		if (*j > 0 && res[*j - 1] != ' ')
			res[(*j)++] = ' ';
		res[(*j)++] = line[*i];
		if ((line[*i] == '<' || line[*i] == '>') && line[*i + 1] == line[*i])
			res[(*j)++] = line[++(*i)];
		if (line[*i + 1] && line[*i + 1] != ' ')
			res[(*j)++] = ' ';
		return (1);
	}
	return (0);
}

char	*normalize_token_line(const char *line)
{
	char	*res;
	int		i;
	int		j;
	char	quote;

	res = ft_calloc((ft_strlen(line) * 3) + 1, sizeof(char));
	if (!res)
		return (NULL);
	i = 0;
	j = 0;
	quote = 0;
	while (line[i])
	{
		update_quote(line, &quote, i);
		if (!quote && append_separator(res, line, &i, &j))
			;
		else
			res[j++] = line[i];
		i++;
	}
	res[j] = '\0';
	return (res);
}
