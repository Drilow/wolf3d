/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adleau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/11 14:11:02 by adleau            #+#    #+#             */
/*   Updated: 2018/01/18 13:11:18 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENGINE_H
# define ENGINE_H
# include <sdl/sdl_wrapper.h>
# include <w3d/w3d.h>
# include <w3d/map.h>
# include <parser/parser.h>

typedef struct			s_engine
{
	t_sdl_wrapper			mainwindow;
	t_parser				parser;
//	struct s_doom			doomengine;
//	struct s_duke			dukeengine;
	char					picker;
}							t_engine;

void					engine(void);

#endif
