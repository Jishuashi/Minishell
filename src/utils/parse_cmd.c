/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louka <louka@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/25 19:04:03 by hchartie          #+#    #+#             */
/*   Updated: 2026/04/29 14:20:24 by louka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	fill_args(t_cmd *cmd, char **tokens, int *i);

t_cmd	**parse_cmd(char **token, t_cmd **cmds, t_env_table *env)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (token[i])
	{
		if (token[i][0] == '|')
		{
			i++;
			continue ;
		}
		cmds[j] = fill_cmd(token, &i, env);
		if (!cmds[j])
			return (NULL);
		j++;
	}
	cmds[j] = NULL;
	return (cmds);
}

t_cmd	*fill_cmd(char **tokens, int *i, t_env_table *env)
{
	t_cmd	*cmd;
	int		argc;

	argc = count_args(tokens, *i);
	cmd = malloc(sizeof(t_cmd) + sizeof(char *) * (argc + 1));
	if (!cmd)
		return (NULL);
	cmd->path = NULL;
	cmd->args = (char **)((char *)cmd + sizeof(t_cmd));
	fill_args(cmd, tokens, i);
	return (cmd);
}

void	push_arg(t_cmd *cmd, char **tokens, int *i, t_env_table *env)
{
	int	j;

	j = 0;
	while (cmd->args[j] != NULL)
		j++;
	if (j == 0)
	{
		cmd->args[j] = ft_strdup(tokens[*i]);
		if (!cmd->args[j])
		{
			(*i)++;
			return ;
		}
		cmd->path = check_path_cmd(tokens[*i], env);
	}
	else
	{
		cmd->args[j] = ft_strdup(tokens[*i]);
		if (!cmd->args[j])
		{
			(*i)++;
			return ;
		}
	}
	(*i)++;
}

char	*check_path_cmd(char *path, t_env_table *env)
{
	char	*path_env;
	char	**paths;
	char	*full_path;
	int		i;

	if (!path)
		return (NULL);
	if (ft_strchr(path, '/'))
		return (ft_strdup(path));
	path_env = get_value("PATH", env);
	if (!path_env)
		return (ft_cmd_not_found_two(path), NULL);
	paths = ft_split(path_env, ':');
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		if (check_acces(i, paths, &full_path, path) == 0)
			return (ft_free_all(paths), full_path);
		i++;
	}
	ft_cmd_not_found(paths, path);
	return (NULL);
}

int	count_args(char **tokens, int i)
{
	int	argc;

	argc = 0;
	while (tokens[i] && tokens[i][0] != '|')
	{
		if (tokens && (tokens[i][0] == '<' || tokens[i][0] == '>'))
		{
			if (tokens[i + 1])
				i += 2;
			else
				i++;
		}
		else
		{
			argc++;
			i++;
		}
	}
	return (argc);
}
