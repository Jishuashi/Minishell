/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_files.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louka <louka@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/25 15:47:37 by hchartie          #+#    #+#             */
/*   Updated: 2026/06/02 16:40:39 by louka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char		*check_file_path(char *path, char type, t_env_table *env);
static int		get_cmd_index(char **tokens, int idx);
static t_file	*create_file_node(char **tokens, int *i, t_env_table *env);
char			*get_file_type(char **tokens, int idx);

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
		file->delimiter = ft_strdup(tokens[++(*i)]);
		file->path = check_file_path(NULL, file->type[0], env);
	}
	else
	{
		file->delimiter = NULL;
		file->path = check_file_path(tokens[++(*i)], file->type[0], env);
	}
	file->cmd_index = cmd_idx;
	return (file);
}

char	*get_file_type(char **tokens, int idx)
{
	char	*res;

	res = "IN";
	if (tokens[idx][0] == '>')
		res = "OUT";
	if (tokens[idx][1] == '<')
		res = "HEREDOC";
	if (tokens[idx][1] == '>')
		res = "APPEND";
	return (res);
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
	int		is_tilde;

	if (type == 'H')
		return (NULL);
	if (!path)
		return (NULL);
	is_tilde = 0;
	if (path[0] == '~')
	{
		is_tilde = 1;
		home = get_env_value("HOME", env);
		path = extend_tilde(path, home);
	}
	if (ft_strchr(path, '/') && path[1] != '/')
		result = ft_strjoin("./", path);
	else if (ft_strchr(path, '/') && path[0] == '.')
		result = ft_strdup(path);
	else
		result = ft_strjoin("./", path);
	if (is_tilde)
		free(path);
	return (result);
}
