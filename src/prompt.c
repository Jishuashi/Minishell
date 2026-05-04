/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchartie <hchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 12:09:53 by louka             #+#    #+#             */
/*   Updated: 2026/05/04 17:09:48 by hchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

volatile sig_atomic_t	g_signal;

static void	temp_print(t_openf **op);

static void	on_sigint(int signum)
{
	(void)signum;
	g_signal = 0;
	write(1, "\n", 1);
	rl_on_new_line();
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
	int		last_status;

	setup_signals();
	args = NULL;
	last_status = 0;
	while (1)
	{
		line = readline(get_prompt());
		if (!line)
			break ;
		if (line[0] != '\0')
			add_history(line);
		args = parse_args(get_token(line, env, last_status), env);
		if (args->nb_file >= 1)
			temp_print(open_files(args));
		if (!args)
			last_status = 1;
		else
			last_status = 0;
		free(line);
		free_args(args);
	}
	return (0);
}

static void	temp_print(t_openf **op)
{
	int	i;

	i = 0;
	while (op[i])
	{
		ft_printf("File %d: status=%d, fd=%d, type=%s\n", i, op[i]->status,
			op[i]->fd, op[i]->type);
		i++;
	}
}
