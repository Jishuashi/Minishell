/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extend.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louka <louka@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 15:23:49 by louka             #+#    #+#             */
/*   Updated: 2026/04/27 16:10:14 by louka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXTEND_H
# define EXTEND_H

typedef struct s_env_table	t_env_table;

char	*extend(char *token, t_env_table *env, int last_status);

#endif