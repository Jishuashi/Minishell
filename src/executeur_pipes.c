/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executeur_pipes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchartie <hchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/14 17:40:09 by louka             #+#    #+#             */
/*   Updated: 2026/06/01 17:33:34 by hchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

static int	alloc_pipe_block(t_exec_res *res, int n_cmds)
{
	res->pipes = malloc(sizeof(int) * 2 * (n_cmds - 1));
	if (!res->pipes)
	{
		free(res->pids);
		return (-1);
	}
	if (fill_pipes(res->pipes, n_cmds - 1) == -1)
	{
		free(res->pids);
		free(res->pipes);
		return (-1);
	}
	return (0);
}

t_openf	**open_and_check(t_args *args)
{
	t_openf	**opens;
	int		i;

	opens = open_files(args);
	if (!opens)
		return (NULL);
	i = 0;
	while (opens[i])
	{
		if (opens[i]->status <= 0)
		{
			if (ft_strncmp(opens[i]->type, "HEREDOC", 7) != 0)
			{
				free_opens(opens);
				return (NULL);
			}
		}
		i++;
	}
	return (opens);
}

int	fill_pipes(int (*pipes)[2], int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		if (pipe(pipes[i]) == -1)
		{
			perror("minishell: pipe");
			return (-1);
		}
		i++;
	}
	return (0);
}

int	alloc_exec_resources(t_args *args, t_exec_res *res)
{
	int	n_cmds;

	if (!args || !args->cmds || !args->cmds[0])
		return (0);
	n_cmds = (int)count_cmds(args->cmds);
	if (n_cmds == 0)
		return (0);
	res->opens = open_and_check(args);
	if (!res->opens)
		return (-1);
	res->pids = malloc(sizeof(pid_t) * n_cmds);
	if (!res->pids)
		return (-1);
	res->pipes = NULL;
	if (n_cmds > 1 && alloc_pipe_block(res, n_cmds) == -1)
		return (-1);
	res->n_cmds = n_cmds;
	return (n_cmds);
}

int	spawn_children(t_exec_res *res, t_args *args, t_env_table *env)
{
	int	i;

	i = 0;
	while (i < res->n_cmds)
	{
		res->pids[i] = fork();
		if (res->pids[i] < 0)
			return (perror("minishell: fork"), -1);
		if (res->pids[i] == 0)
		{
			child_exec_body(i, res, args, env);
			exit(127);
		}
		if (res->n_cmds > 1)
		{
			if (i > 0)
				close(res->pipes[i - 1][0]);
			if (i < res->n_cmds - 1)
				close(res->pipes[i][1]);
		}
		i++;
	}
	return (0);
}
