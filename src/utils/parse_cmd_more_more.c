/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd_more_more.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louka2b <louka2b@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 16:48:50 by louka2b           #+#    #+#             */
/*   Updated: 2026/05/29 16:54:29 by louka2b          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*dup_path_token(char *path)
{
	if (ft_strchr(path, '/'))
		return (ft_strdup(path));
	return (NULL);
}

char	*search_cmd_in_paths(char **paths, char *path)
{
	char	*full_path;
	int		i;

	i = -1;
	while (paths[++i])
	{
		if (check_acces(i, paths, &full_path, path) == 0)
			return (ft_free_all(paths), full_path);
	}
	ft_cmd_not_found(paths, path);
	return (NULL);
}
