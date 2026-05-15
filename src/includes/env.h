/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louka <louka@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 14:00:59 by hchartie          #+#    #+#             */
/*   Updated: 2026/05/15 17:22:26 by louka            ###   ########.fr       */
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
void		print_env(t_env_table *env);
int			calloc_all(char ***var, int **i);
char		*get_value(char	*key, t_env_table *env);
void		set_env_var(char *key, char *value, t_env_table *env);

#endif