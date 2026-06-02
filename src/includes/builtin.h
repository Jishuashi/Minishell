/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louka <louka@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 23:36:10 by louka             #+#    #+#             */
/*   Updated: 2026/06/02 17:25:44 by louka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

int		is_builtin(char *cmd);
int		execute_builtin(t_cmd *cmd, t_env_table *env);
int		apply_builtin_action(t_cmd *cmd, t_env_table *env);
int		execute_exit_builtin(t_cmd *cmd);
void	exit_shell(int status, t_env_table *env);
int		ft_export(char **cmd, t_env_table *env);
int		ft_cd(char **args, t_env_table *env);
int		is_valid_exit_status(char *arg);
void	print_echo(t_cmd *cmd, int i, int opt);
void	ft_echo(t_cmd *cmd);

#endif