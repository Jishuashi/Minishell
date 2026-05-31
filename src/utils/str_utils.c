/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchartie <hchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/31 13:30:10 by hchartie          #+#    #+#             */
/*   Updated: 2026/05/31 13:40:11 by hchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char *ft_strfreejoin(char *s, char *join)
{
	char *temp;

	temp = s;
	s = ft_strjoin(s, join);
	free(temp);
	return (s);
}