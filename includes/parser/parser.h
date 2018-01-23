/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adleau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/11 19:44:38 by adleau            #+#    #+#             */
/*   Updated: 2018/01/21 13:26:56 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include <w3d/w3d.h>
# include <w3d/map.h>

struct s_engine;
struct s_binds;

typedef struct		s_parser
{
	char			*path;
	char			*line;
	char			**parse_tab;
	int				fd;
	int				beenread;
	int				linesread;
	char			done;
	void			(*parse_f)(struct s_engine*, char*);
	t_w3dmap		map;
}					t_parser;

void			parse_binds(struct s_engine *eng, struct s_binds *binds, char *path);

#endif
