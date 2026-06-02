/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executeur_child.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louka <louka@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/14 16:40:18 by louka             #+#    #+#             */
/*   Updated: 2026/06/02 17:21:29 by louka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

static void	apply_single_redir(t_file *file)
{
	t_openf		*here;
	struct stat	st;
	int			fd;

	fd = -1;
	if (!ft_strncmp(file->type, "HEREDOC", 8))
	{
		here = heredoc(file->delimiter);
		if (!here)
			exit(1);
		fd = here->fd;
		free(here);
	}
	else if (!ft_strncmp(file->type, "IN", 2))
	{
		if (stat(file->path, &st) == 0 && S_ISDIR(st.st_mode))
		{
			errno = EISDIR;
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(file->path, 2);
			ft_putstr_fd(": ", 2);
			ft_putstr_fd(strerror(errno), 2);
			ft_putstr_fd("\n", 2);
			exit(1);
		}
		fd = open(file->path, O_RDONLY);
	}
	else if (!ft_strncmp(file->type, "OUT", 3))
		fd = open(file->path, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	else if (!ft_strncmp(file->type, "APPEND", 7))
		fd = open(file->path, O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (fd < 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(file->path, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
		exit(1);
	}
	if (!ft_strncmp(file->type, "IN", 2)
		|| !ft_strncmp(file->type, "HEREDOC", 8))
	{
		if (dup2(fd, 0) == -1)
		{
			perror("minishell");
			exit(1);
		}
	}
	else if (dup2(fd, 1) == -1)
	{
		perror("minishell");
		exit(1);
	}
	if (fd > 2)
		close(fd);
}

void	child_exec_body(int i, t_exec_res *res, t_args *args,
		t_env_table *env)
{
	int	status;

	restore_child_signals();
	child_setup_pipes(i, res);
	child_apply_redirs(i, res, args);
	child_close_opens(res);
	if (args->cmds[i] && args->cmds[i]->args
		&& is_builtin(args->cmds[i]->args[0]))
	{
		status = execute_builtin(args->cmds[i], env);
		if (status < 0)
			exit(-status - 1);
		exit(status);
	}
	else
		run_child(args->cmds[i], env);
}

void	child_setup_pipes(int i, t_exec_res *res)
{
	int	j;

	if (res->n_cmds <= 1)
		return ;
	if (i > 0)
		dup2(res->pipes[i - 1][0], 0);
	if (i < res->n_cmds - 1)
		dup2(res->pipes[i][1], 1);
	j = 0;
	while (j < res->n_cmds - 1)
	{
		close(res->pipes[j][0]);
		close(res->pipes[j][1]);
		j++;
	}
}

void	child_apply_redirs(int i, t_exec_res *res, t_args *args)
{
	int	j;

	(void)res;
	j = 0;
	while (args->files && args->files[j])
	{
		if (args->files[j]->cmd_index == i)
			apply_single_redir(args->files[j]);
		j++;
	}
}

void	child_close_opens(t_exec_res *res)
{
	int	j;

	if (!res->opens)
		return ;
	j = 0;
	while (res->opens[j])
	{
		if (res->opens[j]->fd > 2)
			close(res->opens[j]->fd);
		j++;
	}
}
{
	int	j;

	if (!res->opens)
		return ;

	j = 0;
	while (res->opens[j])
	{
		if (res->opens[j]->fd > 2)
			close(res->opens[j]->fd);
		j++;
	}
}
