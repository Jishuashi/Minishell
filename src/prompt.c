/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louka2b <louka2b@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 12:09:53 by louka             #+#    #+#             */
/*   Updated: 2026/05/29 14:03:56 by louka2b          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

volatile sig_atomic_t	g_signal;

void	on_sigint(int signum)
{
	(void)signum;
	g_signal = SIGINT;
	printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	setup_signals(void)
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
	int		last_status;
	char	*status_str;

	setup_signals();
	args = NULL;
	last_status = 0;
	set_env_value("?", "0", env);
	while (1)
	{
		line = readline(get_prompt());
		if (!line)
			exit_shell(last_status, env);
		last_status = process_command_line(line, env, &args, last_status);
		status_str = ft_itoa(last_status);
		if (status_str)
		{
			set_env_value("?", status_str, env);
			free(status_str);
		}
		free(line);
		free_args(args);
	}
	return (0);
}
