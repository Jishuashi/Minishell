/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchartie <hchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 12:09:53 by louka             #+#    #+#             */
/*   Updated: 2026/04/25 21:52:18 by hchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

volatile sig_atomic_t	g_signal;

static void	on_sigint(int signum)
{
	(void)signum;
	g_signal = 0;
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

int	shell_loop(t_env_table *env)
{
	char	*line;
	t_args	*args;

	setup_signals();
	args = NULL;
	while (1)
	{
		line = readline(get_prompt());
		if (!line)
			break ;
		if (line[0] != '\0')
			add_history(line);
		args = parse_args(get_token(line, env));
		free(line);
		free_args(args);
	}
	return (0);
}
