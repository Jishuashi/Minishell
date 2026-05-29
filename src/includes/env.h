/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louka2b <louka2b@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 14:00:59 by hchartie          #+#    #+#             */
/*   Updated: 2026/05/29 16:33:07 by louka2b          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H
# include "../libft/libft.h"

typedef struct s_env
{
	char	*name;
	char	*value;
}	t_env;
typedef struct s_env_table
{
	t_env	*table;
	size_t	size;
}	t_env_table;

t_env_table	*create_env(char *envp[]);
char		*get_env_value(char	*key, t_env_table *env);
void		set_env_value(char *key, char *value, t_env_table *env);
void		increment_shlvl(t_env_table *env);
void		add_env_value(char *key, char *value, t_env_table *env);
void		remove_env_value(char *key, t_env_table *env);

#endif