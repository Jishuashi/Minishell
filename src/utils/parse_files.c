/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_files.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchartie <hchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/25 15:47:37 by hchartie          #+#    #+#             */
/*   Updated: 2026/05/06 15:29:02 by hchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*check_file_path(char *path);
char		*get_file_type(char **token, int idx);

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
		file->path = check_file_path(tokens[++i]);
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
	if (tokens[idx][1] == '<' )
		res = "HEREDOC";
	if (tokens[idx][1] == '>')
		res = "APPEND";
	return (res);
}

static char	*check_file_path(char *path)
{
	if (ft_strchr(path, '/') && path[1] != '/')
		return (ft_strjoin("./", path));
	else if (ft_strchr(path, '/') && path[0] == '.')
		return (ft_strdup(path));
	else
		return (ft_strjoin("./", path));
}
