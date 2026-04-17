/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louka <louka@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 12:02:28 by louka             #+#    #+#             */
/*   Updated: 2026/04/17 11:14:55 by louka            ###   ########.fr       */
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

extern volatile sig_atomic_t	g_signal;

const char	*get_prompt(void);
int			shell_loop(void);

#endif