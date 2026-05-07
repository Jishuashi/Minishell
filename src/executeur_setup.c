/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executeur_setup.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louka <louka@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 12:36:30 by louka             #+#    #+#             */
/*   Updated: 2026/05/07 13:02:33 by louka            ###   ########.fr       */
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

static int	pid_error(pid_t pid)
{
	if (pid < 0)
	{
		ft_putstr_fd("minishell: fork: ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
		return (1);
	}
	return (0);
}

static int	create_child(pid_t pid, int status, t_args *args, t_env_table *env)
{
	struct sigaction	sa_int;
	struct sigaction	sa_int_old;

	if (pid_error(pid) == 1)
		return (1);
	if (pid == 0)
		run_child(args->cmds[0], env);
	ft_bzero(&sa_int, sizeof(sa_int));
	sa_int.sa_handler = SIG_IGN;
	sigemptyset(&sa_int.sa_mask);
	sigaction(SIGINT, &sa_int, &sa_int_old);
	while (waitpid(pid, &status, 0) == -1)
	{
		if (errno != EINTR)
		{
			sigaction(SIGINT, &sa_int_old, NULL);
			return (1);
		}
	}
	sigaction(SIGINT, &sa_int_old, NULL);
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
