/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchartie <hchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 13:33:21 by hchartie          #+#    #+#             */
/*   Updated: 2026/05/30 15:59:53 by hchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <fcntl.h>
# include <signal.h>
# include <string.h>
# include <sys/wait.h>
# include <termios.h>
# include <stdio.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <errno.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <dirent.h>
# include <stddef.h>

# include "../libft/libft.h"
# include "prompt.h"
# include "env.h"
# include "utils.h"
# include "token.h"
# include "extend.h"
# include "args.h"
# include "parse_files.h"
# include "open_file.h"
# include "builtin.h"
# include "executeur_pipes.h"
# include "parse_cmd.h"
# include "free.h"
# include "executeur.h"

#endif