/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executeur_redirs.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louka <louka@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/14 16:40:18 by louka             #+#    #+#             */
/*   Updated: 2026/06/02 17:21:29 by louka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

static void	check_is_dir(char *path)
{
	struct stat	st;

	if (stat(path, &st) == 0 && S_ISDIR(st.st_mode))
	{
		errno = EISDIR;
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
		exit(1);
	}
}

static int	get_redir_fd(t_file *file)
{
	t_openf	*here;
	int		fd;

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
		check_is_dir(file->path);
		fd = open(file->path, O_RDONLY);
	}
	else if (!ft_strncmp(file->type, "OUT", 3))
		fd = open(file->path, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	else if (!ft_strncmp(file->type, "APPEND", 7))
		fd = open(file->path, O_WRONLY | O_APPEND | O_CREAT, 0644);
	return (fd);
}

static void	print_redir_error(char *path)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(path, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putstr_fd("\n", 2);
	exit(1);
}

static void	apply_single_redir(t_file *file)
{
	int	fd;

	fd = get_redir_fd(file);
	if (fd < 0)
		print_redir_error(file->path);
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
