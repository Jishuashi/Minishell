/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchartie <hchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 14:04:42 by hchartie          #+#    #+#             */
/*   Updated: 2026/05/27 15:28:22 by hchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

typedef struct s_file	t_file;

size_t	count_double_char(char **tab);
void	ft_free_all(char **pfree);
int		check_files(t_file	*file);
void	print_env(t_env_table *env);

#endif