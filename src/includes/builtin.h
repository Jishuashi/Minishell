/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louka2b <louka2b@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 23:36:10 by louka             #+#    #+#             */
/*   Updated: 2026/05/29 14:32:44 by louka2b          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

int	is_builtin(char *cmd);
int	execute_builtin(t_cmd *cmd, t_env_table *env);
void	exit_shell(int status, t_env_table *env);
void    ft_export(char **cmd, t_env_table *env);

#endif