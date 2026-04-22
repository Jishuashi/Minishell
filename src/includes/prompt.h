/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchartie <hchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 12:02:28 by louka             #+#    #+#             */
/*   Updated: 2026/04/22 15:27:12 by hchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROMPT_H
# define PROMPT_H

# include <signal.h>
# include <unistd.h>
# include <termios.h>
# include <stdio.h>
# include <readline/history.h>
# include <readline/readline.h>

typedef struct s_env_table t_env_table;
typedef struct s_env t_env; 
extern volatile sig_atomic_t	g_signal;

const char	*get_prompt(void);
int			shell_loop(t_env_table *env);

#endif