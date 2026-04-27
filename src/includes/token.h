/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchartie <hchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 12:30:32 by louka             #+#    #+#             */
/*   Updated: 2026/04/27 16:56:32 by hchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

char	**get_token(char *line, t_env_table *env, int last_status);
char	**split_token(char **token, char *line, t_env_table *env,
			int last_status);
int		len_token(char	**tokens);

#endif