/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adleau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/11 19:44:38 by adleau            #+#    #+#             */
/*   Updated: 2018/01/18 13:10:59 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include <w3d/w3d.h>
# include <w3d/map.h>

typedef struct		s_parser
{
	char			**parse_tab;
	int				fd;
	int				beenread;
	int				linesread;
	t_w3dmap		map;
}					t_parser;

#endif
