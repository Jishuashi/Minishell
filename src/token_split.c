/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louka <louka@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 21:45:48 by louka             #+#    #+#             */
/*   Updated: 2026/06/02 17:25:44 by louka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

static int	token_len(const char *line, int i)
{
	int		len;
	char	quote;

	len = 0;
	quote = 0;
	while (line[i] && (line[i] != ' ' || quote))
	{
		if (is_quote(line[i]) && (!quote || quote == line[i]))
			quote = toggle_quote(quote, line[i]);
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
		}
		dst[k++] = line[(*i)++];
	}
	dst[k] = '\0';
}

static int	append_split_token(char **slot, t_split_token_ctx *ctx)
{
	int		quoted;
	char	*expanded;

	*slot = ft_calloc(token_len(ctx->line, *ctx->i) + 1, sizeof(char));
	if (!*slot)
		return (-1);
	copy_token(*slot, ctx->line, ctx->i);
	quoted = has_quote(*slot);
	expanded = extend(*slot, ctx->env, ctx->last_status);
	if (!expanded)
		return (-1);
	if (expanded[0] == '\0' && !quoted)
	{
		free(expanded);
		*slot = NULL;
		return (0);
	}
	if (quoted)
	{
		expanded = mark_quoted(expanded);
		if (!expanded)
			return (-1);
	}
	*slot = expanded;
	return (1);
}

char	**split_token(char **token, char *line, t_env_table *env,
		int last_status)
{
	t_split_token_ctx	ctx;
	int					i;
	int					j;
	int					ret;

	ctx.line = line;
	ctx.env = env;
	ctx.last_status = last_status;
	i = 0;
	j = 0;
	while (line[i])
	{
		while (line[i] && line[i] == ' ')
			i++;
		if (!line[i])
			break ;
		ctx.i = &i;
		ret = append_split_token(token + j, &ctx);
		if (ret < 0)
			return (NULL);
		if (ret > 0)
			j++;
	}
	token[j] = NULL;
	return (token);
}
