/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_extend.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louka <louka@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 15:22:10 by louka             #+#    #+#             */
/*   Updated: 2026/04/24 11:59:41 by louka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

static char	*extract_var_name(char *token, int start, int *end)
{
	int		len;
	char	*var_name;
	int		i;

	len = 0;
	i = start;
	while (token[i] && (ft_isalnum(token[i]) || token[i] == '_'))
	{
		len++;
		i++;
	}
	*end = i;
	var_name = ft_calloc(len + 1, sizeof(char));
	if (!var_name)
		return (NULL);
	ft_strlcpy(var_name, token + start, len + 1);
	return (var_name);
}

static void	need_extend(char **var, t_env_table *env, int *i, char *token)
{
	int	var_end;

	var[0] = extract_var_name(token, i[0] + 1, &var_end);
	if (!var[0])
		return ;
	if (var[0][0])
	{
		var[1] = get_value(var[0], env);
		if (var[1])
			i[1] += ft_strlcpy(var[3] + i[1], var[1], 2048 - i[1]);
		free(var[0]);
		i[0] = var_end;
	}
	else
	{
		free(var[0]);
		var[3][i[1]++] = token[i[0]];
		i[0]++;
	}
}

static void	single_quote(char *token)
{
	int	i;

	i = 0;
	while (token[i])
	{
		if (token[i] == 31)
			token[i] = '$';
		i++;
	}
}

static char	*replace_var(char *token, t_env_table *env)
{
	char	**var;
	int		*i;

	if (!calloc_tout(&var, &i))
		return (token);
	i[0] = 0;
	i[1] = 0;
	while (token[i[0]])
	{
		if (token[i[0]] == '$')
			need_extend(var, env, i, token);
		else
		{
			var[3][i[1]++] = token[i[0]];
			i[0]++;
		}
	}
	var[3][i[1]] = '\0';
	free(i);
	free(token);
	token = var[3];
	free(var);
	single_quote(token);
	return (token);
}

char	*extend(char *token, t_env_table *env)
{
	if (!token || !env)
		return (token);
	return (replace_var(token, env));
}
