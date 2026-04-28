/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_acces.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louka <louka@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 12:14:13 by louka             #+#    #+#             */
/*   Updated: 2026/04/28 12:54:13 by louka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_acces(int i, char **paths, char *full_path, char *path)
{
	full_path = ft_strjoin(paths[i], "/");
	if (!full_path)
		return (ft_free_all(paths), NULL);
	full_path = ft_strjoin_free(full_path, path);
	if (!full_path)
		return (ft_free_all(paths), NULL);
	if (access(full_path, X_OK) == 0)
		return (ft_free_all(paths), full_path);
	free(full_path);
	return (i++);
}