/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd_more.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louka <louka@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 12:14:13 by louka             #+#    #+#             */
/*   Updated: 2026/04/29 14:24:50 by louka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_acces(int i, char **paths, char **full_path, char *path)
{
	char	*tmp;

	tmp = ft_strjoin(paths[i], "/");
	if (!tmp)
		return (-1);
	*full_path = ft_strjoin(tmp, path);
	free(tmp);
	if (!*full_path)
		return (-1);
	if (access(*full_path, X_OK) == 0)
		return (0);
	free(*full_path);
	*full_path = NULL;
	return (1);
}

void	ft_cmd_not_found_two(char *path)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(path, 2);
	ft_putstr_fd(": command not found\n", 2);
}

void	ft_cmd_not_found(char **paths, char *path)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(path, 2);
	ft_putstr_fd(": command not found\n", 2);
	ft_free_all(paths);
}

void	fill_args(t_cmd *cmd, char **tokens, int *i)
{
	int	j;

	while (tokens[*i] && tokens[*i][0] != '|')
	{
		if (tokens[*i][0] == '<' || tokens[*i][0] == '>')
		{
			if (tokens[*i + 1])
				*i += 2;
			else
				*i += 1;
		}
		else
			push_arg(cmd, tokens, i, NULL);
	}
	j = 0;
	while (cmd->args[j] != NULL)
		j++;
	cmd->args[j] = NULL;
}
