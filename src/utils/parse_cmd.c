/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchartie <hchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/25 19:04:03 by hchartie          #+#    #+#             */
/*   Updated: 2026/05/31 14:30:41 by hchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
	int		j;

	argc = count_args(tokens, *i);
	cmd = malloc(sizeof(t_cmd) + sizeof(char *) * (argc + 2));
	if (!cmd)
		return (NULL);
	cmd->path = NULL;
	cmd->args = (char **)((char *)cmd + sizeof(t_cmd));
	j = 0;
	while (j <= (argc + 1))
	{
		cmd->args[j] = NULL;
		j++;
	}
	fill_args(cmd, tokens, i, env);
	return (cmd);
}

void	push_arg(t_cmd *cmd, char **tokens, int *i, t_env_table *env)
{
	int		j;
	char	*arg;
	char	*exp;

	j = 0;
	while (cmd->args[j])
		j++;
	arg = tokens[*i];
	exp = NULL;
	if (arg && arg[0] == '~')
		exp = extend_tilde(ft_strdup(arg), get_env_value("HOME", env));
	if (exp)
		arg = exp;
	cmd->args[j] = ft_strdup(arg);
	if (!cmd->args[j])
		return (free(exp), ++(*i), (void)0);
	if (j == 0)
		cmd->path = check_path_cmd(arg, env);
	free(exp);
	++(*i);
}

char	*check_path_cmd(char *path, t_env_table *env)
{
	char	*path_env;
	char	**paths;

	if (!path)
		return (NULL);
	if (is_builtin(path))
		return (NULL);
	if (ft_strchr(path, '/'))
		return (dup_path_token(path));
	path_env = get_env_value("PATH", env);
	if (!path_env)
		return (ft_cmd_not_found_two(path), NULL);
	paths = ft_split(path_env, ':');
	if (!paths)
		return (NULL);
	return (search_cmd_in_paths(paths, path));
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
