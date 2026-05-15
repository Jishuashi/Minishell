/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executeur_child.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louka <louka@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/14 16:40:18 by louka             #+#    #+#             */
/*   Updated: 2026/05/15 16:53:02 by louka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"
#include "includes/executeur_pipes.h"

void	child_exec_body(int i, t_exec_res *res, t_args *args,
		t_env_table *env)
{
	restore_child_signals();
	child_setup_pipes(i, res);
	child_apply_redirs(i, res, args);
	child_close_opens(res);
	run_child(args->cmds[i], env);
}

void	child_setup_pipes(int i, t_exec_res *res)
{
	int j;

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

void	child_apply_redirs(int i, t_exec_res *res, t_args *args)
{
	int j;

	j = 0;
	while (args->files && args->files[j])
	{
		if (args->files[j]->cmd_index == i)
		{
			if (!ft_strncmp(res->opens[j]->type, "IN", 2)
				|| !ft_strncmp(res->opens[j]->type, "HEREDOC", 7))
				dup2(res->opens[j]->fd, 0);
			else
				dup2(res->opens[j]->fd, 1);
		}
		j++;
	}
}

void	child_close_opens(t_exec_res *res)
{
	int j;

	j = 0;
	while (res->opens[j])
	{
		if (res->opens[j]->fd > 2)
			close(res->opens[j]->fd);
		j++;
	}
}
