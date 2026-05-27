/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchartie <hchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 14:46:53 by hchartie          #+#    #+#             */
/*   Updated: 2026/05/27 17:05:42 by hchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

static void	heredoc_child(char *delimiter)
{
	char	*line;
	int		fd;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_IGN);
	fd = open("/tmp/heredoc", O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (fd == -1)
		exit(1);
	while (1)
	{
		line = readline("heredoc > ");
		if (!line || !ft_strncmp(line, delimiter, ft_strlen(delimiter) + 1))
			break ;
		ft_putstr_fd(line, fd);
		ft_putstr_fd("\n", fd);
		free(line);
	}
	free(line);
	close(fd);
	exit(0);
}

t_openf	*heredoc(char *delimiter)
{
	pid_t	pid;
	int		status;
	t_openf	*res;

	pid = fork();
	if (pid == 0)
		heredoc_child(delimiter);
	signal(SIGINT, SIG_IGN);
	waitpid(pid, &status, 0);
	setup_signals();
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		g_signal = SIGINT;
		printf("\n");
		return (NULL);
	}
	res = (t_openf *)malloc(sizeof(t_openf));
	if (!res)
		return (NULL);
	res->fd = open("/tmp/heredoc", O_RDONLY);
	if (res->fd == -1)
		return (free(res), NULL);
	res->status = 0;
	res->type = "HEREDOC";
	return (res);
}
