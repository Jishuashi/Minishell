/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louka <louka@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/25 22:34:42 by hchartie          #+#    #+#             */
/*   Updated: 2026/06/02 17:17:58 by louka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

static int		ft_open(t_file *file);
static t_openf	*process_file(t_file *file, int *failed);
static void		free_open_files(t_openf **opens);
static void		print_open_error(t_file *file);

t_openf	**open_files(t_args *args)
{
	int		i;
	int		failed;
	t_openf	**res;

	i = 0;
	failed = 0;
	res = (t_openf **)ft_calloc((args->nb_file + 1), sizeof(t_openf *));
	if (!res)
		return (NULL);
	while (args->files[i])
	{
		res[i] = process_file(args->files[i], &failed);
		if (!res[i])
		{
			free_open_files(res);
			return (NULL);
		}
		i++;
	}
	res[i] = NULL;
	return (res);
}

static void	free_open_files(t_openf **opens)
{
	int	i;

	i = 0;
	while (opens && opens[i])
	{
		if (opens[i]->fd > 2)
			close(opens[i]->fd);
		free(opens[i]);
		i++;
	}
	free(opens);
}

static t_openf	*process_file(t_file *file, int *failed)
{
	t_openf	*res;

	if (!ft_strncmp(file->type, "HEREDOC", 8))
		return (heredoc(file->delimiter));
	res = (t_openf *)malloc(sizeof(t_openf));
	if (!res)
		return (NULL);
	res->type = file->type;
	if (*failed)
	{
		res->status = -1;
		res->fd = -1;
		return (res);
	}
	res->fd = ft_open(file);
	if (res->fd < 0)
	{
		print_open_error(file);
		res->status = -1;
		*failed = 1;
	}
	else
		res->status = 1;
	return (res);
}

static void	print_open_error(t_file *file)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(file->path, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putstr_fd("\n", 2);
}

static int	ft_open(t_file *file)
{
	if (!ft_strncmp("IN", file->type, 2))
		return (open(file->path, O_RDONLY));
	if (!ft_strncmp("OUT", file->type, 3))
	{
		if (!ft_strncmp(file->path, "/dev/null", 9))
			return (open(file->path, O_WRONLY));
		return (open(file->path, O_WRONLY | O_TRUNC | O_CREAT, 0644));
	}
	if (!ft_strncmp("APPEND", file->type, 7))
	{
		if (!ft_strncmp(file->path, "/dev/null", 9))
			return (open(file->path, O_WRONLY));
		return (open(file->path, O_WRONLY | O_APPEND | O_CREAT, 0644));
	}
	return (0);
}
