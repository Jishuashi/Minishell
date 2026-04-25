/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchartie <hchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/25 21:24:50 by hchartie          #+#    #+#             */
/*   Updated: 2026/04/25 21:48:38 by hchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FREE_H
# define FREE_H

typedef struct s_cmd	t_cmd;
typedef struct s_file	t_file;
typedef struct s_args	t_args;

int	free_cmds(t_cmd **cmds);
int	free_files(t_file **files);
int	free_args(t_args *args);
int	free_token(char **tokens);
int	free_env(t_env_table *env);

#endif