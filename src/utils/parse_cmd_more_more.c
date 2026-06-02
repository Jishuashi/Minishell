/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd_more_more.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchartie <hchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 16:48:50 by louka2b           #+#    #+#             */
/*   Updated: 2026/06/01 17:30:07 by hchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*expand_tilde_if_needed(char *arg, t_env_table *env)
{
	char	*dup_arg;
	char	*exp;

	if (!arg || arg[0] != '~')
		return (arg);
	dup_arg = ft_strdup(arg);
	if (!dup_arg)
		return (arg);
	exp = extend_tilde(dup_arg, get_env_value("HOME", env));
	if (exp)
		return (exp);
	free(dup_arg);
	return (arg);
}

char	*dup_path_token(char *path)
{
	if (ft_strchr(path, '/'))
		return (ft_strdup(path));
	return (NULL);
}

char	*search_cmd_in_paths(char **paths, char *path)
{
	char	*full_path;
	int		i;

	i = -1;
	while (paths[++i])
	{
		if (check_acces(i, paths, &full_path, path) == 0)
			return (ft_free_all(paths), full_path);
	}
	ft_cmd_not_found(paths, path);
	return (NULL);
}

char	*check_path_cmd(char *path, t_env_table *env)
{
	char	*path_env;
	char	**paths;

	if (!path)
		return (NULL);
	if (is_builtin(path))
		return (NULL);
	if (ft_strchr(path, '/'))
		return (dup_path_token(path));
	path_env = get_env_value("PATH", env);
	if (!path_env)
		return (ft_cmd_not_found_two(path), NULL);
	paths = ft_split(path_env, ':');
	if (!paths)
		return (NULL);
	return (search_cmd_in_paths(paths, path));
}

int	count_args(char **tokens, int i)
{
	int	argc;

	argc = 0;
	while (tokens[i] && tokens[i][0] != '|')
	{
		if (tokens && (tokens[i][0] == '<' || tokens[i][0] == '>'))
		{
			if (tokens[i + 1])
				i += 2;
			else
				i++;
		}
		else
		{
			argc++;
			i++;
		}
	}
	return (argc);
}
