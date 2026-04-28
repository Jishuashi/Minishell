/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldeplace <ldeplace@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/25 19:04:25 by hchartie          #+#    #+#             */
/*   Updated: 2026/04/28 13:23:43 by ldeplace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_CMD_H
# define PARSE_CMD_H

typedef	struct s_cmd		t_cmd;
typedef	struct s_env_table	t_env_table;

t_cmd	**parse_cmd(char **token, t_cmd **cmds, t_env_table *env);
char	*check_path_cmd(char *path, t_env_table *env);
int		count_args(char **tokens, int i);
t_cmd	*fill_cmd(char **tokens, int *i, t_env_table *env);
int		check_acces(int i, char **paths, char **full_path, char *path);
void	push_arg(t_cmd *cmd, char **tokens, int *i, int *j, t_env_table *env);

#endif