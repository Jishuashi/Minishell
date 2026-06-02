/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louka <louka@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 12:30:32 by louka             #+#    #+#             */
/*   Updated: 2026/06/02 17:02:06 by louka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

typedef struct s_split_token_ctx
{
	char		*line;
	int			*i;
	t_env_table	*env;
	int			last_status;
}	t_split_token_ctx;

char	**get_token(char *line, t_env_table *env, int last_status);
char	**split_token(char **token, char *line, t_env_table *env,
			int last_status);
int		len_token(char	**tokens);
char	*normalize_token_line(const char *line);
char	toggle_quote(char quote, char c);
int		is_quote(char c);
int		has_quote(char *token);
char	*mark_quoted(char *expanded);

#endif