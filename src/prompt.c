/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louka <louka@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 12:09:53 by louka             #+#    #+#             */
/*   Updated: 2026/04/17 12:58:16 by louka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

volatile sig_atomic_t	g_signal;

static void	on_sigint(int signum)
{
	(void)signum;
	g_signal = SIGINT;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

static void	setup_signals(void)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;
	struct termios		term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	ft_bzero(&sa_int, sizeof(sa_int));
	ft_bzero(&sa_quit, sizeof(sa_quit));
	sa_int.sa_handler = on_sigint;
	sigemptyset(&sa_int.sa_mask);
	sa_quit.sa_handler = SIG_IGN;
	sigemptyset(&sa_quit.sa_mask);
	sigaction(SIGINT, &sa_int, NULL);
	sigaction(SIGQUIT, &sa_quit, NULL);
}

const char	*get_prompt(void)
{
	return ("minishell> ");
}

int	shell_loop(void)
{
	char	*line;

	setup_signals();
	while (1)
	{
		line = readline(get_prompt());
		if (g_signal == SIGINT)
		{
			g_signal = 0;
			free(line);
		}
		if (!line)
		{
			ft_printf("exit");
			break ;
		}
		if (line[0] != '\0')
			add_history(line);
		token(line);
		free(line);
	}
	return (0);
}

int	main(void)
{
	g_signal = 0;
	shell_loop();
	return (0);
}
