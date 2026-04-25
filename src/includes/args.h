/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchartie <hchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 15:24:05 by hchartie          #+#    #+#             */
/*   Updated: 2026/04/25 03:22:59 by hchartie         ###   ########.fr       */
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

typedef struct s_files
{
	char	*path;
	char	*type;
}	t_files;

typedef struct s_args
{
	t_cmd	*cmds;
	t_files	*files;
}	t_args;

t_args	*parse_args(char	**tokens);

#endif