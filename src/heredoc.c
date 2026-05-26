/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louka <louka@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 14:46:53 by hchartie          #+#    #+#             */
/*   Updated: 2026/05/26 23:12:27 by louka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

static	t_openf	*get_here_file(char *content);

t_openf	*heredoc(char *delimiter)
{
	char	*line;
	char	*res;
	char	*temp;

	res = NULL;
	while (1)
	{
		line = readline("heredoc > ");
		if (!line || !ft_strncmp(line, delimiter, ft_strlen(delimiter) + 1))
			return (free(line), get_here_file(res));
		temp = res;
		res = ft_strjoin(res, line);
		free(temp);
		temp = res;
		res = ft_strjoin(res, "\n");
		free(temp);
		free(line);
	}
}

static	t_openf	*get_here_file(char *content)
{
	t_openf	*res;

	res = (t_openf *)malloc(sizeof(t_openf));
	if (!res)
		return (NULL);
	res->fd = open("/tmp/heredoc", O_RDWR | O_TRUNC | O_CREAT, 0644);
	if (content)
	{
		ft_putstr_fd(content, res->fd);
		free(content);
		lseek(res->fd, 0, SEEK_SET);
	}
	res->status = 0;
	res->type = "HEREDOC";
	return (res);
}
