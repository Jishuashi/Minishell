/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executeur.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louka <louka@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 12:23:15 by louka             #+#    #+#             */
/*   Updated: 2026/05/07 13:03:13 by louka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTEUR_H
# define EXECUTEUR_H

int		execute_args(t_args *args, t_env_table *env);
void	run_child(t_cmd *cmd, t_env_table *env);
void	restore_child_signals(void);
void	free_envp_exec(char **envp);
char	**build_envp(t_env_table *env);
size_t	count_cmds(t_cmd **cmds);
int		process_command_line(char *line, t_env_table *env,
			t_args **args, int last_status);

#endif
