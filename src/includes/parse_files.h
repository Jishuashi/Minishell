/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_files.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchartie <hchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/25 18:03:54 by hchartie          #+#    #+#             */
/*   Updated: 2026/04/25 18:09:21 by hchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_FILES_H
# define PARSE_FILES_H

typedef struct s_file	t_file;

t_file	**parse_files(char **tokens, t_file **files, int len);

#endif