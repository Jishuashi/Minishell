/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchartie <hchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/25 22:34:42 by hchartie          #+#    #+#             */
/*   Updated: 2026/05/04 17:09:23 by hchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

static int	ft_open(t_file *file);

t_openf	**open_files(t_args *args)
{
	int		i;
	t_file	*current;
	t_openf	**res;

	i = 0;
	res = (t_openf **)malloc(sizeof(t_openf *) * (args->nb_file + 1));
	if (!res)
		return (NULL);
	while (args->files[i])
	{
		current = args->files[i];
		res[i] = (t_openf *)malloc(sizeof(t_openf));
		if (!res[i])
		{
			free(res);
			return (NULL);
		}
		res[i]->status = check_files(current);
		res[i]->type = current->type;
		res[i]->fd = ft_open(current);
		i++;
	}
	res[i] = NULL;
	return (res);
}

static int	ft_open(t_file *file)
{
	if (!ft_strncmp("IN", file->type, 2))
		return (open(file->path, O_RDONLY));
	if (!ft_strncmp("OUT", file->type, 3))
		return (open(file->path, O_WRONLY | O_TRUNC | O_CREAT, 0644));
	if (!ft_strncmp("APPEND", file->type, 7))
		return (open(file->path, O_WRONLY | O_APPEND | O_CREAT, 0644));
	return (0);
}
