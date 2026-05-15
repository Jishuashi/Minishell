/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchartie <hchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/25 22:34:42 by hchartie          #+#    #+#             */
/*   Updated: 2026/05/11 13:57:15 by hchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

static int	ft_open(t_file *file);

t_openf	**open_files(t_args *args)
{
	int		i;
	t_openf	**res;

	i = 0;
	res = (t_openf **)ft_calloc((args->nb_file + 1), sizeof(t_openf *));
	if (!res)
		return (NULL);
	while (args->files[i])
	{
		if (!ft_strncmp(args->files[i]->type, "HEREDOC", 8))
			res[i] = heredoc(args->files[i]->delimiter);
		else
		{
			res[i] = (t_openf *)malloc(sizeof(t_openf));
			if (!res[i])
				return (free(res), NULL);
			res[i]->status = check_files(args->files[i]);
			res[i]->type = args->files[i]->type;
			res[i]->fd = ft_open(args->files[i]);
		}
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
