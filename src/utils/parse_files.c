/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_files.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louka <louka@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/25 15:47:37 by hchartie          #+#    #+#             */
/*   Updated: 2026/05/15 16:51:55 by louka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*check_file_path(char *path, char type);
static int	get_cmd_index(char **tokens, int idx);
char		*get_file_type(char **tokens, int idx);

t_file	**parse_files(char **tokens, t_file **files, int len)
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
		file = malloc(sizeof(t_file));
		if (!file)
			return (NULL);
		file->type = get_file_type(tokens, i);
		if (file->type[0] == 'H')
			file->delimiter = ft_strdup(tokens[++i]);
		else
			file->delimiter = NULL;
		file->path = check_file_path(tokens[++i], file->type[0]);
		file->cmd_index = get_cmd_index(tokens, i);
		if (j < len)
			files[j++] = file;
	}
	files[j] = NULL;
	return (files);
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

static char	*check_file_path(char *path, char type)
{
	if (type == 'H')
		return (NULL);
	if (ft_strchr(path, '/') && path[1] != '/')
		return (ft_strjoin("./", path));
	if (ft_strchr(path, '/') && path[0] == '.')
		return (ft_strdup(path));
	return (ft_strjoin("./", path));
}
