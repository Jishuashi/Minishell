/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executeur_setup.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louka <louka@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 12:36:30 by louka             #+#    #+#             */
/*   Updated: 2026/05/06 00:00:21 by louka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	process_command_line(char *line, t_env_table *env,
		t_args **args, int last_status)
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

static  int	create_child(pid_t pid, int status, t_args *args, t_env_table *env)
{
	if (pid < 0)
	{
		ft_putstr_fd("minishell: fork: ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
		return (1);
	}
	if (pid == 0)
		run_child(args->cmds[0], env);
	while (waitpid(pid, &status, 0) == -1)
	{
		if (errno != EINTR)
			return (1);
	}
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (1);
}

int	execute_args(t_args *args, t_env_table *env)
{
	pid_t	pid;
	int		status;

	status = 0;
	if (!args || !args->cmds || !args->cmds[0])
		return (0);
	if (!args->cmds[0]->path)
		return (127);
	pid = fork();
	return (create_child(pid, status, args, env));
}
