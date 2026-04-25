/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchartie <hchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/25 19:04:25 by hchartie          #+#    #+#             */
/*   Updated: 2026/04/25 20:13:37 by hchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_CMD_H
# define PARSE_CMD_H

typedef struct s_cmd	t_cmd;

t_cmd	**parse_cmd(char **token, t_cmd **cmds);

#endif