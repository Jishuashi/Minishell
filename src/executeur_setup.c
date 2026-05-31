/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executeur_setup.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchartie <hchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 12:36:30 by louka             #+#    #+#             */
/*   Updated: 2026/05/31 14:23:11 by hchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	process_command_line(char *line, t_env_table *env, t_args **args,
		int last_status)
{
	char	**tokens;

	if (line[0])
		add_history(line);
	tokens = get_token(line, env, last_status);
	if (!tokens)
		return (1);
	*args = parse_args(tokens, env);
	if (!*args)
		return (1);
	if ((*args)->cmds && (*args)->cmds[0])
		return (execute_args(*args, env));
	return (0);
}

static void	close_parent_pipes(int (*pipes)[2], int n_cmds)
{
	int	k;

	if (!pipes)
		return ;
	k = 0;
	while (k < n_cmds - 1)
	{
		close(pipes[k][0]);
		close(pipes[k][1]);
		k++;
	}
}

static int	wait_children_and_status(pid_t *pids, int n_cmds)
{
	int	i;
	int	status;
	int	last_status;

	status = 0;
	last_status = 0;
	i = 0;
	while (i < n_cmds)
	{
		if (waitpid(pids[i], &status, 0) != -1 && i == n_cmds - 1)
		{
			if (WIFEXITED(status))
				last_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				last_status = 128 + WTERMSIG(status);
		}
		i++;
	}
	return (last_status);
}

int	execute_args(t_args *args, t_env_table *env)
{
	t_exec_res	res;
	int			ret;

	ret = alloc_exec_resources(args, &res);
	if (ret <= 0)
	{
		if (ret == 0)
			return (0);
		return (1);
	}
	if (res.n_cmds == 1 && args->cmds && args->cmds[0] && args->cmds[0]->args
		&& is_builtin(args->cmds[0]->args[0]))
		return (run_builtin(&res, args, env));
	if (spawn_children(&res, args, env) == -1)
		return (1);
	close_parent_pipes(res.pipes, res.n_cmds);
	close_opens(res.opens);
	ret = wait_children_and_status(res.pids, res.n_cmds);
	free(res.pids);
	if (res.pipes)
		free(res.pipes);
	return (ret);
}
