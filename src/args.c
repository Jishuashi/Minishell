/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchartie <hchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 15:23:11 by hchartie          #+#    #+#             */
/*   Updated: 2026/04/25 18:41:58 by hchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

static int		count_cmd(char **tokens);
static int		count_file(char **tokens);
static t_args	*fill_args(t_args *args, char **tokens);

t_args	*parse_args(char **tokens)
{
	t_args	*args;

	args = (t_args *)malloc(sizeof(t_args));
	if (!args)
		return (NULL);
	args->cmds = (t_cmd *)malloc(sizeof(t_cmd) * count_cmd(tokens));
	if (!args->cmds)
	{
		free(args);
		return (NULL);
	}
	args->files = (t_file **)malloc(sizeof(t_file *) * (count_file(tokens)+1));
	if (!args->files)
	{
		free(args->cmds);
		free(args);
		return (NULL);
	}
	args = fill_args(args, tokens);
	free(tokens);
	return (args);
}

static int	count_cmd(char **tokens)
{
	int	i;
	int	res;
	int	len;

	i = 0;
	res = 0;
	len = len_token(tokens);
	while (i < len)
	{
		if (tokens[i][0] == '<' || tokens[i][0] == '>')
			i += 2;
		else if (tokens[i][0] == '|')
			i++;
		else
		{
			res++;
			while (i < len && tokens[i][0] != '<' && tokens[i][0] != '>'
				&& tokens[i][0] != '|')
				i++;
		}
	}
	return (res);
}

static int	count_file(char **tokens)
{
	int	i;
	int	res;
	int	len;

	i = 0;
	res = 0;
	len = len_token(tokens);
	while (i < len)
	{
		if (tokens[i][0] == '<' || tokens[i][0] == '>')
			res++;
		i++;
	}
	return (res);
}

static	t_args	*fill_args(t_args *args, char **tokens)
{
	int	i;

	args->files = parse_files(tokens, args->files, count_file(tokens));
	if (!args->files)
		return (NULL);
	i = 0;
	while (i < count_file(tokens))
	{
		printf("Path : %s\n", args->files[i]->path);
		printf("Type : %s\n", args->files[i]->type);
		printf("Del : %s\n", args->files[i]->delimiter);
		i++;
	}
	return (args);
}
