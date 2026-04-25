/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchartie <hchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 15:24:05 by hchartie          #+#    #+#             */
/*   Updated: 2026/04/25 17:43:53 by hchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARGS_H
# define ARGS_H

typedef struct s_cmd
{
	char	*name;
	char	*binary;
	char	*args[];
}	t_cmd;

typedef struct s_file
{
	char	*path;
	char	*type;
	char	*delimiter;
}	t_file;

typedef struct s_args
{
	t_cmd	*cmds;
	t_file	**files;
}	t_args;

t_args	*parse_args(char	**tokens);

#endif