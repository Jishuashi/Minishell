/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executeur_pipes.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louka <louka@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/14 17:40:09 by louka             #+#    #+#             */
/*   Updated: 2026/05/15 16:53:02 by louka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTEUR_PIPES_H
# define EXECUTEUR_PIPES_H

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executeur_pipes.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louka <louka@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/14 17:40:09 by louka             #+#    #+#             */
/*   Updated: 2026/05/15 16:48:45 by louka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

typedef struct s_exec_res
{
	t_openf	**opens;
	pid_t		*pids;
	int		(*pipes)[2];
	int		n_cmds;
}	t_exec_res;

t_openf	**open_and_check(t_args *args);
int	fill_pipes(int (*pipes)[2], int n);
int	alloc_exec_resources(t_args *args, t_env_table *env, t_exec_res *res);
int	spawn_children(t_exec_res *res, t_args *args, t_env_table *env);
void	child_exec_body(int i, t_exec_res *res, t_args *args,
		t_env_table *env);
void	child_setup_pipes(int i, t_exec_res *res);
void	child_apply_redirs(int i, t_exec_res *res, t_args *args);
void	child_close_opens(t_exec_res *res);

#endif
