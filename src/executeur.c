/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executeur.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louka <louka@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 11:32:47 by louka             #+#    #+#             */
/*   Updated: 2026/05/07 13:02:58 by louka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

size_t	count_cmds(t_cmd **cmds)
{
	size_t	count;

	count = 0;
	if (!cmds)
		return (0);
	while (cmds[count])
		count++;
	return (count);
}

char	**build_envp(t_env_table *env)
{
	char	**envp;
	size_t	i;
	char	*name_and_equal;

	i = 0;
	if (!env)
	{
		envp = ft_calloc(1, sizeof(char *));
		return (envp);
	}
	envp = ft_calloc(env->size + 1, sizeof(char *));
	if (!envp)
		return (NULL);
	while (i < env->size)
	{
		name_and_equal = ft_strjoin(env->table[i].name, "=");
		if (!name_and_equal)
			return (free_envp_exec(envp), NULL);
		envp[i] = ft_strjoin(name_and_equal, env->table[i].value);
		free(name_and_equal);
		if (!envp[i])
			return (free_envp_exec(envp), NULL);
		i++;
	}
	return (envp);
}

void	free_envp_exec(char **envp)
{
	size_t	i;

	if (!envp)
		return ;
	i = 0;
	while (envp[i])
	{
		free(envp[i]);
		i++;
	}
	free(envp);
}

void	restore_child_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	run_child(t_cmd *cmd, t_env_table *env)
{
	char	**envp;

	restore_child_signals();
	if (!cmd || !cmd->path)
		_exit(127);
	envp = build_envp(env);
	if (!envp)
		_exit(1);
	execve(cmd->path, cmd->args, envp);
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd->path, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putstr_fd("\n", 2);
	free_envp_exec(envp);
	if (errno == ENOENT)
		_exit(127);
	_exit(126);
}
