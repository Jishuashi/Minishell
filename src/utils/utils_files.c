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
