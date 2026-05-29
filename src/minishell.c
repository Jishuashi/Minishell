/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louka2b <louka2b@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 13:33:25 by hchartie          #+#    #+#             */
/*   Updated: 2026/05/29 16:44:52 by louka2b          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	main(int ac, char *av[], char *envp[])
{
	t_env_table	*env;

	(void)av;
	if (ac != 1)
		return (1);
	env = create_env(envp);
	shell_loop(env, 0);
	free_env(env);
	return (0);
}
