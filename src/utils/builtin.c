/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louka <louka@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/30 16:57:12 by ldplace           #+#    #+#             */
/*   Updated: 2026/06/02 16:03:36 by louka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_valid_exit_status(char *arg)
{
	int	i;

	if (!arg || !arg[0])
		return (0);
	i = 0;
	if (arg[i] == '+' || arg[i] == '-')
		i++;
	if (!ft_isdigit(arg[i]))
		return (0);
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
			return (0);
		i++;
	}
	return (1);
}

void	print_echo(t_cmd *cmd, int i, int opt)
{
	if (cmd->args[i] != NULL)
	{
		printf("%s", cmd->args[i]);
		if (cmd->args[i + 1] != NULL)
		{
			printf(" ");
			print_echo(cmd, i + 1, opt);
		}
	}
}

void	ft_echo(t_cmd *cmd)
{
	int	i;
	int	opt;

	i = 1;
	opt = 0;
	while (cmd->args[i] != NULL && !ft_strncmp(cmd->args[i], "-n", 3))
	{
		opt++;
		i++;
	}
	print_echo(cmd, i, opt);
	if (!opt)
		printf("\n");
}

int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (!ft_strncmp(cmd, "echo", 5) || !ft_strncmp(cmd, "cd", 3)
		|| !ft_strncmp(cmd, "pwd", 4) || !ft_strncmp(cmd, "export", 7)
		|| !ft_strncmp(cmd, "unset", 6) || !ft_strncmp(cmd, "env", 4)
		|| !ft_strncmp(cmd, "exit", 5))
		return (1);
	return (0);
}

int	execute_builtin(t_cmd *cmd, t_env_table *env)
{
	return (apply_builtin_action(cmd, env));
}
