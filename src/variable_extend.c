/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_extend.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louka <louka@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 15:22:10 by louka             #+#    #+#             */
/*   Updated: 2026/04/29 14:26:08 by louka            ###   ########.fr       */
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
	t_extend	*all;

	all = malloc(sizeof (t_extend));
	if (!all)
		return (token);
	all->env = env;
	all->token = token;
	if (!calloc_all(&all->var, &all->i))
		return (token);
	all->in_single_quote = 0;
	all->in_double_quote = 0;
	all->i[0] = 0;
	all->i[1] = 0;
	all->i[2] = last_status;
	while (all->token[all->i[0]])
		ft_check_quote(all);
	all->var[3][all->i[1]] = '\0';
	free(all->i);
	free(token);
	token = all->var[3];
	free(all->var);
	free(all);
	return (token);
}

char	*extend(char *token, t_env_table *env, int last_status)
{
	if (!token || !env)
		return (token);
	return (replace_var(token, env, last_status));
}
