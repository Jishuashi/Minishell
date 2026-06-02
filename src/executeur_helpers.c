/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executeur_helpers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchartie <hchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 17:00:00 by auto              #+#    #+#             */
/*   Updated: 2026/06/02 16:41:24 by hchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	close_opens(t_openf **opens)
{
	int	i;

	i = 0;
	while (opens && opens[i])
	{
		if (opens[i]->fd > 2)
			close(opens[i]->fd);
		i++;
	}
}

void	free_opens(t_openf **opens)
{
	int	i;

	i = 0;
	while (opens && opens[i])
	{
		if (opens[i]->fd > 2)
			close(opens[i]->fd);
		free(opens[i]);
		i++;
	}
	free(opens);
}

static void	setup_builtin_redir(t_exec_res *res, t_args *args, int saved[2])
{
	int	j;

	saved[0] = dup(0);
	saved[1] = dup(1);
	j = 0;
	while (args->files && args->files[j])
	{
		if (args->files[j]->cmd_index == 0 && res->opens && res->opens[j])
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

int	run_builtin(t_exec_res *res, t_args *args, t_env_table *env)
{
	int	status;
	int	saved[2];

	setup_builtin_redir(res, args, saved);
	status = execute_builtin(args->cmds[0], env);
	dup2(saved[0], 0);
	dup2(saved[1], 1);
	close(saved[0]);
	close(saved[1]);
	if (res->opens)
		free_opens(res->opens);
	free(res->pids);
	if (res->pipes)
		free(res->pipes);
	return (status);
}
