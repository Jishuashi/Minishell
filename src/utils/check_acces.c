/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_acces.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldeplace <ldeplace@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 12:14:13 by louka             #+#    #+#             */
/*   Updated: 2026/04/28 13:27:01 by ldeplace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_acces(int i, char **paths, char **full_path, char *path)
{
	char *tmp;

	tmp = ft_strjoin(paths[i], "/");
	if (!tmp)
		return (-1);
	*full_path = ft_strjoin(tmp, path);
	free(tmp);
	if (!*full_path)
		return (-1);
	if (access(*full_path, X_OK) == 0)
		return (-1);
	free(*full_path);
	return (i++);
}