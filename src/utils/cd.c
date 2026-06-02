/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louka <louka@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/30 13:51:37 by hchartie          #+#    #+#             */
/*   Updated: 2026/06/02 17:29:33 by louka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <limits.h>

int			is_directory(const char *path);
static void	exec_cd(char *path, t_env_table *env);

int	ft_cd(char **args, t_env_table *env)
{
	char	*home;
	char	*path;
	int		tilde;

	home = get_env_value("HOME", env);
	path = args[1];
	if (!path)
		path = home;
	tilde = 0;
	if (path && path[0] == '~')
		tilde = 1;
	if (tilde)
		path = extend_tilde(path, home);
	if (!path || access(path, F_OK) || !is_directory(path))
		return (perror("cd"), 1);
	exec_cd(path, env);
	if (tilde)
		free(path);
	return (0);
}

static void	exec_cd(char *path, t_env_table *env)
{
	char	buffer[PATH_MAX];
	char	*oldpwd;

	oldpwd = get_env_value("PWD", env);
	if (oldpwd)
		set_env_value("OLDPWD", oldpwd, env);
	if (chdir(path) == -1)
		return (perror("cd"));
	getcwd(buffer, sizeof(buffer));
	set_env_value("PWD", buffer, env);
}

int	is_directory(const char *path)
{
	DIR	*dir;

	dir = opendir(path);
	if (dir != NULL)
	{
		closedir(dir);
		return (1);
	}
	return (0);
}
