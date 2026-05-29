/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executeur_helpers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auto <auto@local>                           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 17:00:00 by auto              #+#    #+#             */
/*   Updated: 2026/05/29 17:00:00 by auto             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	close_opens(t_openf **opens)

{
    int i;

    i = 0;
    while (opens && opens[i])
    {
        if (opens[i]->fd > 2)
            close(opens[i]->fd);
        i++;
    }
}

int	run_builtin(t_exec_res *res, t_args *args, t_env_table *env)
{
    int	status;

    status = execute_builtin(args->cmds[0], env);
    if (res->opens)
        close_opens(res->opens);
    free(res->pids);
    if (res->pipes)
        free(res->pipes);
    return (status);
}
