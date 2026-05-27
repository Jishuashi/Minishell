/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louka <louka@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 23:36:23 by louka             #+#    #+#             */
/*   Updated: 2026/05/27 16:06:27 by louka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	print_echo(t_cmd *cmd, int i)
{
	if (cmd->args[i] != NULL)
	{
		printf("%s", cmd->args[i]);
		if (cmd->args[i + 1] != NULL)
		{
			printf(" ");
			print_echo(cmd, i + 1);
		}
	}
}

static void	ft_echo(t_cmd *cmd)
{
	if (cmd->args[1][0] == '-')
	{
		if (ft_strlen(cmd->args[1]) == 2)
		{
			if (cmd->args[1][1] == 'n')
			{
				print_echo(cmd, 2);
				return ;
			}
		}
	}
	print_echo(cmd, 1);
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
	if (!ft_strncmp(cmd->args[0], "pwd", 4))
		printf("%s\n", get_value("PWD", env));
	if (!ft_strncmp(cmd->args[0], "env", 4))
		print_env(env);
	if (!ft_strncmp(cmd->args[0], "echo", 4))
		ft_echo(cmd);
	return (1);
}
