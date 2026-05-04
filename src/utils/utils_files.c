/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_files.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchartie <hchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 15:43:17 by hchartie          #+#    #+#             */
/*   Updated: 2026/05/04 16:32:03 by hchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_files(t_file	*file)
{
	if (!ft_strncmp("OUT", file->type, 3)
		|| !ft_strncmp("APPEND", file->type, 7))
	{
		if (access(file->path, F_OK) == 0 && access(file->path, W_OK) == -1)
		{
			ft_putstr_fd(strerror(errno), 2);
			ft_putstr_fd(": ", 2);
			ft_putstr_fd(file->path, 2);
			ft_putstr_fd("\n", 2);
			return (-1);
		}
	}
	else if (!ft_strncmp("IN", file->type, 2))
	{
		if (access(file->path, F_OK) == -1 || access(file->path, R_OK) == -1)
		{
			ft_putstr_fd(strerror(errno), 2);
			ft_putstr_fd(": ", 2);
			ft_putstr_fd(file->path, 2);
			ft_putstr_fd("\n", 2);
			return (0);
		}
	}
	return (1);
}
