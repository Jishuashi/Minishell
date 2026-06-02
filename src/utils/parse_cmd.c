/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchartie <hchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/25 19:04:03 by hchartie          #+#    #+#             */
/*   Updated: 2026/06/02 17:25:44 by louka            ###   ########.fr       */
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
		if (cmds[j]->args[0] != NULL)
			j++;
		else
			free(cmds[j]);
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

static void	clean_push_arg(int quoted, char *arg, char *clean, char *token)
{
	if (quoted)
	{
		if (arg != clean)
			free(arg);
		free(clean);
	}
	else if (arg != token)
		free(arg);
}

static char	*get_clean_arg(char *token, int *quoted)
{
	*quoted = (token[0] == '\1');
	if (*quoted)
		return (ft_strdup(token + 1));
	return (token);
}

void	push_arg(t_cmd *cmd, char **tokens, int *i, t_env_table *env)
{
	int		j;
	int		quoted;
	char	*arg;
	char	*clean;

	j = 0;
	while (cmd->args[j])
		j++;
	clean = get_clean_arg(tokens[*i], &quoted);
	if (quoted && !clean)
		return (++(*i), (void)0);
	arg = expand_tilde_if_needed(clean, env);
	cmd->args[j] = ft_strdup(arg);
	if (!cmd->args[j])
	{
		clean_push_arg(quoted, arg, clean, tokens[*i]);
		return (++(*i), (void)0);
	}
	if (j == 0)
		cmd->path = check_path_cmd(arg, env);
	clean_push_arg(quoted, arg, clean, tokens[*i]);
	++(*i);
}
