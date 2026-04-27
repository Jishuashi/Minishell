/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchartie <hchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/25 19:04:03 by hchartie          #+#    #+#             */
/*   Updated: 2026/04/27 16:52:16 by hchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*check_path_cmd(char *path);
static int	count_args(char **tokens, int i);
t_cmd		*fill_cmd(char **tokens, int *i);
void		push_arg(t_cmd *cmd, char **tokens, int *i, int *j);

t_cmd	**parse_cmd(char **token, t_cmd **cmds)
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
		cmds[j] = fill_cmd(token, &i);
		if (!cmds[j])
			return (NULL);
		j++;
	}
	cmds[j] = NULL;
	return (cmds);
}

t_cmd	*fill_cmd(char **tokens, int *i)
{
	t_cmd	*cmd;
	int		j;
	int		argc;

	argc = count_args(tokens, *i);
	cmd = malloc(sizeof(t_cmd) + sizeof(char *) * (argc + 1));
	if (!cmd)
		return (NULL);
	cmd->path = NULL;
	cmd->args = (char **)((char *)cmd + sizeof(t_cmd));
	j = 0;
	while (tokens[*i] && tokens[*i][0] != '|')
	{
		if (tokens[*i][0] == '<' || tokens[*i][0] == '>')
		{
			if (tokens[*i + 1])
				*i += 2;
			else
				(*i)++;
		}
		else
			push_arg(cmd, tokens, i, &j);
	}
	cmd->args[j] = NULL;
	return (cmd);
}

void	push_arg(t_cmd *cmd, char **tokens, int *i, int *j)
{
	if (*j != 0)
		cmd->args[*j] = ft_strdup(tokens[*i]);
	else
		cmd->args[*j] = check_path_cmd(tokens[*i]);
	if (!cmd->args[*j])
		return ;
	if (*j == 0)
	{
		cmd->path = check_path_cmd(tokens[*i]);
		if (!cmd->path)
			return ;
	}
	(*j)++;
	(*i)++;
}

static char	*check_path_cmd(char *path)
{
	if (!path)
		return (NULL);
	if (ft_strchr(path, '/'))
		return (ft_strdup(path));
	else
		return (ft_strjoin("/bin/", path));
}

static int	count_args(char **tokens, int i)
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
