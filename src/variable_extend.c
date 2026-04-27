/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_extend.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldeplace <ldeplace@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 15:22:10 by louka             #+#    #+#             */
/*   Updated: 2026/04/27 19:28:25 by ldeplace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

char	*extract_var_name(char *token, int start, int *end)
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

void	need_extend(char **var, t_env_table *env, int *i, char *token)
{
	int		var_end;

	if (token[i[0] + 1] == '?')
		return (if_token(i[2], i, var));
	var[0] = extract_var_name(token, i[0] + 1, &var_end);
	if (!var[0])
		return ;
	if (!var[0][0])
	{
		free(var[0]);
		var[3][i[1]++] = token[i[0]];
		i[0]++;
		return ;
	}
	var[1] = get_value(var[0], env);
	if (var[1])
		i[1] += ft_strlcpy(var[3] + i[1], var[1], 2048 - i[1]);
	free(var[0]);
	i[0] = var_end;
}

void	append_char(char *dst, int *dst_i, char c)
{
	dst[*dst_i] = c;
	(*dst_i)++;
}

static char	*replace_var(char *token, t_env_table *env, int last_status)
{
	char		**var;
	int			*i;
	int			in_single_quote;
	int			in_double_quote;
	t_extend	*all;

	all = malloc(sizeof t_extend);
	ft_put_in_struct(all, token, var, i);
	if (!calloc_all(&all->var, &i))
		return (token);
	i[0] = 0;
	i[1] = 0;
	i[2] = last_status;
	in_single_quote = 0;
	in_double_quote = 0;
	while (token[i[0]])
	{
		
	}
	var[3][i[1]] = '\0';
	free(i);
	free(token);
	token = all->var[i];
	free(all->var);
	return (all->token);
}

char	*extend(char *token, t_env_table *env, int last_status)
{
	if (!token || !env)
		return (token);
	return (replace_var(token, env, last_status));
}
