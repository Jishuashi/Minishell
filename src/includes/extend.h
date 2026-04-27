/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extend.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louka <louka@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 15:23:49 by louka             #+#    #+#             */
/*   Updated: 2026/04/27 19:14:43 by louka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXTEND_H
# define EXTEND_H

typedef struct s_env_table	t_env_table;
typedef struct s_extend
{
	int         in_single_quote;
	int     	in_double_quote;
    char        *token;
    t_env_table *env
}	t_extend;

char		*extend(char *token, t_env_table *env, int last_status);
char		*extract_var_name(char *token, int start, int *end);
void		need_extend(char **var, t_env_table *env, int *i, char *token);
void		append_char(char *dst, int *dst_i, char c);
void		if_token(int last_status, int *i, char **var);

#endif