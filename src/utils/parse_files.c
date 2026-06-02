/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_files.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louka <louka@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/25 15:47:37 by hchartie          #+#    #+#             */
/*   Updated: 2026/06/02 17:35:15 by louka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char		*check_file_path(char *path, char type, t_env_table *env);
static int		get_cmd_index(char **tokens, int idx);
static t_file	*create_file_node(char **tokens, int *i, t_env_table *env);

t_file	**parse_files(char **tokens, t_file **files, int len, t_env_table *env)
{
	int		i;
	int		j;
	t_file	*file;

	i = -1;
	j = 0;
	while (tokens[++i] && tokens[i + 1])
	{
		if (tokens[i][0] != '<' && tokens[i][0] != '>')
			continue ;
		file = create_file_node(tokens, &i, env);
		if (!file)
			return (NULL);
		if (j < len)
			files[j++] = file;
	}
	files[j] = NULL;
	return (files);
}

static t_file	*create_file_node(char **tokens, int *i, t_env_table *env)
{
	t_file	*file;
	int		cmd_idx;

	cmd_idx = get_cmd_index(tokens, *i);
	file = malloc(sizeof(t_file));
	if (!file)
		return (NULL);
	file->type = get_file_type(tokens, *i);
	if (file->type[0] == 'H')
	{
		file->delimiter = strip_quote_marker(tokens[++(*i)]);
		file->path = check_file_path(NULL, file->type[0], env);
	}
	else
	{
		file->delimiter = NULL;
		file->path = check_file_path(strip_quote_marker(tokens[++(*i)]),
				file->type[0], env);
	}
	file->cmd_index = cmd_idx;
	return (file);
}

static int	get_cmd_index(char **tokens, int idx)
{
	int	k;
	int	cmd_idx;

	k = 0;
	cmd_idx = 0;
	while (k < idx)
	{
		if (tokens[k][0] == '|')
			cmd_idx++;
		k++;
	}
	return (cmd_idx);
}

static char	*check_file_path(char *path, char type, t_env_table *env)
{
	char	*home;
	char	*result;
	int		i;

	if (type == 'H' || !path)
		return (NULL);
	i = 0;
	while (path[i] == ' ' || path[i] == '\t')
		i++;
	if (i > 0)
		ft_memmove(path, path + i, ft_strlen(path + i) + 1);
	if (path[0] == '~')
	{
		home = get_env_value("HOME", env);
		path = extend_tilde(path, home);
	}
	if (path[0] == '/' || path[0] == '.')
		result = ft_strdup(path);
	else
		result = ft_strjoin("./", path);
	free(path);
	return (result);
}
