/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executeur_child.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchartie <hchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/14 16:40:18 by louka             #+#    #+#             */
/*   Updated: 2026/06/01 17:29:21 by hchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

static void	apply_single_redir(t_exec_res *res, int i)
{
	if (res->opens[i]->fd < 0)
	{
		perror("minishell");
		exit(1);
	}
	if (!ft_strncmp(res->opens[i]->type, "IN", 2)
		|| !ft_strncmp(res->opens[i]->type, "HEREDOC", 7))
	{
		if (dup2(res->opens[i]->fd, 0) == -1)
		{
			perror("minishell");
			exit(1);
		}
	}
	else
	{
		if (dup2(res->opens[i]->fd, 1) == -1)
		{
			perror("minishell");
			exit(1);
		}
	}
}

void	child_exec_body(int i, t_exec_res *res, t_args *args,
		t_env_table *env)
{
	restore_child_signals();
	child_setup_pipes(i, res);
	child_apply_redirs(i, res, args);
	child_close_opens(res);
	if (args->cmds[i] && args->cmds[i]->args
		&& is_builtin(args->cmds[i]->args[0]))
		execute_builtin(args->cmds[i], env);
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

void	child_apply_redirs(int i, t_exec_res *res, t_args *args)
{
	int	j;

	j = 0;
	while (args->files && args->files[j])
	{
		if (args->files[j]->cmd_index == i)
			apply_single_redir(res, j);
		j++;
	}
}

void	child_close_opens(t_exec_res *res)
{
	int	j;

	j = 0;
	while (res->opens[j])
	{
		if (res->opens[j]->fd > 2)
			close(res->opens[j]->fd);
		j++;
	}
}
