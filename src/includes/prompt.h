/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louka2b <louka2b@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 12:02:28 by louka             #+#    #+#             */
/*   Updated: 2026/05/29 16:45:14 by louka2b          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROMPT_H
# define PROMPT_H

typedef struct s_env_table		t_env_table;
typedef struct s_env			t_env;
extern volatile sig_atomic_t	g_signal;

const char	*get_prompt(void);
int			shell_loop(t_env_table *env, int last_status);
void		setup_signals(void);
void		on_sigint(int signum);

#endif