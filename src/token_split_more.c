/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_split_more.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louka <louka@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 14:35:58 by louka             #+#    #+#             */
/*   Updated: 2026/06/02 16:06:09 by louka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	is_quote(char c)
{
	return (c == '"' || c == '\'');
}

char	toggle_quote(char quote, char c)
{
	if (quote == c)
		return (0);
	return (c);
}