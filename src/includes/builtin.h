/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchartie <hchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 23:36:10 by louka             #+#    #+#             */
/*   Updated: 2026/05/30 14:21:45 by hchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

int		is_builtin(char *cmd);
int		execute_builtin(t_cmd *cmd, t_env_table *env);
void	exit_shell(int status, t_env_table *env);
void	ft_export(char **cmd, t_env_table *env);
void	ft_cd(char **args, t_env_table *env);

#endif