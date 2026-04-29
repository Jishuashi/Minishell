/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchartie <hchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/25 19:04:25 by hchartie          #+#    #+#             */
/*   Updated: 2026/04/29 15:59:50 by hchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_CMD_H
# define PARSE_CMD_H

typedef struct s_cmd		t_cmd;
typedef struct s_env_table	t_env_table;

t_cmd	**parse_cmd(char **token, t_cmd **cmds, t_env_table *env);
char	*check_path_cmd(char *path, t_env_table *env);
int		count_args(char **tokens, int i);
t_cmd	*fill_cmd(char **tokens, int *i, t_env_table *env);
int		check_acces(int i, char **paths, char **full_path, char *path);
void	push_arg(t_cmd *cmd, char **tokens, int *i, t_env_table *env);
void	ft_cmd_not_found(char **paths, char *path);
void	ft_cmd_not_found_two(char *path);
void	fill_args(t_cmd *cmd, char **tokens, int *i, t_env_table *env);

#endif