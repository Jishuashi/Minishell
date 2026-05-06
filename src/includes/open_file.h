/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_file.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchartie <hchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/25 22:35:55 by hchartie          #+#    #+#             */
/*   Updated: 2026/05/06 15:07:38 by hchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPEN_FILE_H
# define OPEN_FILE_H

typedef struct s_openf
{
	int		status;
	int		fd;
	char	*type;
}	t_openf;

t_openf	**open_files(t_args *args);
t_openf	*heredoc(char *delimiter);

#endif