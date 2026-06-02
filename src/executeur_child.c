/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executeur_child.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louka <louka@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/14 16:40:18 by louka             #+#    #+#             */
/*   Updated: 2026/06/02 17:21:29 by louka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	child_exec_body(int i, t_exec_res *res, t_args *args,
		t_env_table *env)
{
	int	status;

	restore_child_signals();
	child_setup_pipes(i, res);
	child_apply_redirs(i, res, args);
	child_close_opens(res);
	if (args->cmds[i] && args->cmds[i]->args
		&& is_builtin(args->cmds[i]->args[0]))
	{
		status = execute_builtin(args->cmds[i], env);
		if (status < 0)
			exit(-status - 1);
		exit(status);
	}
	else
		run_child(args->cmds[i], env);
}

void	child_setup_pipes(int i, t_exec_res *res)
{
	int	j;

	if (res->n_cmds <= 1)
		return ;
	if (i > 0)
		dup2(res->pipes[i - 1][0], 0);
	if (i < res->n_cmds - 1)
		dup2(res->pipes[i][1], 1);
	j = 0;
	while (j < res->n_cmds - 1)
	{
		close(res->pipes[j][0]);
		close(res->pipes[j][1]);
		j++;
	}
}

void	child_close_opens(t_exec_res *res)
{
	int	j;

	if (!res->opens)
		return ;
	j = 0;
	while (res->opens[j])
	{
		if (res->opens[j]->fd > 2)
			close(res->opens[j]->fd);
		j++;
	}
}
