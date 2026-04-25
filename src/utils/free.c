/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchartie <hchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/25 21:24:16 by hchartie          #+#    #+#             */
/*   Updated: 2026/04/25 21:49:00 by hchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	free_cmds(t_cmd **cmds)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!cmds)
		return (1);
	while (cmds[i])
	{
		free(cmds[i]->path);
		j = 0;
		while (cmds[i]->args[j])
		{
			free(cmds[i]->args[j]);
			j++;
		}
		free (cmds[i]);
		i++;
	}
	free(cmds);
	return (0);
}

int	free_files(t_file **files)
{
	int	i;

	i = 0;
	if (!files)
		return (1);
	while (files[i])
	{
		free(files[i]->path);
		if (files[i]->delimiter)
			free(files[i]->delimiter);
		free(files[i]);
		i++;
	}
	free(files);
	return (0);
}

int	free_args(t_args *args)
{
	if (!args)
		return (1);
	free_cmds(args->cmds);
	free_files(args->files);
	free(args);
	return (0);
}

int	free_token(char **tokens)
{
	char	**start;

	if (!tokens)
		return (1);
	start = tokens;
	while (*tokens)
	{
		free(*tokens);
		tokens++;
	}
	free(start);
	return (0);
}

int	free_env(t_env_table *env)
{
	size_t	i;

	if (!env)
		return (1);
	i = 0;
	while (i < env->size)
	{
		free(env->table[i].name);
		free(env->table[i].value);
		i++;
	}
	free(env->table);
	free(env);
	return (0);
}
