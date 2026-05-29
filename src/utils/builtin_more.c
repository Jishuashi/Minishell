/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_more.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louka2b <louka2b@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 13:55:33 by louka2b           #+#    #+#             */
/*   Updated: 2026/05/29 14:03:54 by louka2b          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdlib.h>

void	exit_shell(int status, t_env_table *env)
{
	if (env)
		free_env(env);
	printf("exit\n");
	rl_clear_history();
	exit(status);
}