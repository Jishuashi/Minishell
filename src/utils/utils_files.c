/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_files.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louka <louka@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 15:43:17 by hchartie          #+#    #+#             */
/*   Updated: 2026/06/02 17:34:14 by louka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <fcntl.h>
#include <stdio.h>

static int	print_file_err(char *path)
{
	ft_putstr_fd("minishell: ", 2);
	perror(path);
	return (0);
}

int	check_files(t_file *file)
{
	int	fd;

	if (!file || !file->path || file->type[0] == 'H')
		return (1);
	if (file->type[0] == 'I')
		fd = open(file->path, O_RDONLY);
	else if (file->type[0] == 'O')
		fd = open(file->path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (file->type[0] == 'A')
		fd = open(file->path, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		return (1);
	if (fd < 0)
		return (print_file_err(file->path));
	close(fd);
	return (1);
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

char	*strip_quote_marker(char *token)
{
	if (token && token[0] == '\1')
		return (ft_strdup(token + 1));
	return (ft_strdup(token));
}
