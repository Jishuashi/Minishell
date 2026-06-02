/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_more_more.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louka <louka@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 16:00:21 by louka             #+#    #+#             */
/*   Updated: 2026/06/02 16:59:39 by louka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	execute_exit_builtin(t_cmd *cmd)
{
	if (!cmd->args[1])
		return (-1);
	if (!is_valid_exit_status(cmd->args[1]))
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(cmd->args[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		return (-3);
	}
	return (-(ft_atoi(cmd->args[1]) + 1));
}

int	apply_builtin_action(t_cmd *cmd, t_env_table *env)
{
	if (!ft_strncmp(cmd->args[0], "pwd", 4))
		ft_printf("%s\n", get_env_value("PWD", env));
	else if (!ft_strncmp(cmd->args[0], "env", 4))
		print_env(env);
	else if (!ft_strncmp(cmd->args[0], "echo", 4))
		ft_echo(cmd);
	else if (!ft_strncmp(cmd->args[0], "exit", 4))
		return (execute_exit_builtin(cmd));
	else if (!ft_strncmp(cmd->args[0], "unset", 5))
	{
		if (cmd->args[1])
			remove_env_value(cmd->args[1], env);
	}
	else if (!ft_strncmp(cmd->args[0], "export", 7))
		ft_export(cmd->args, env);
	else if (!ft_strncmp(cmd->args[0], "cd", 3))
		return (ft_cd(cmd->args, env));
	return (0);
}
