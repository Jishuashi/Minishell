/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchartie <hchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 15:24:05 by hchartie          #+#    #+#             */
/*   Updated: 2026/04/27 16:36:15 by hchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARGS_H
# define ARGS_H

typedef struct s_openf	t_openf;

typedef struct s_cmd
{
	char	*path;
	char	**args;
	t_openf	*in;
	t_openf	**out;
}	t_cmd;

typedef struct s_file
{
	char	*path;
	char	*type;
	char	*delimiter;
}	t_file;

typedef struct s_args
{
	t_cmd	**cmds;
	t_file	**files;
}	t_args;

t_args	*parse_args(char	**tokens);

#endif