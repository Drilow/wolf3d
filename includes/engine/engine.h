/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adleau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/11 14:11:02 by adleau            #+#    #+#             */
/*   Updated: 2018/01/23 15:41:42 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENGINE_H
# define ENGINE_H
# include <sdl/sdl_wrapper.h>
# include <w3d/w3d.h>
# include <w3d/map.h>
# include <parser/parser.h>

typedef struct			s_binds
{
	SDL_Scancode		up;
	SDL_Scancode		down;
	SDL_Scancode		left;
	SDL_Scancode		right;
	SDL_Scancode		menu;
}						t_binds;

typedef struct			s_engine
{
	t_sdl_wrapper			mainwindow;
	t_parser				parser;
//	struct s_doom			doomengine;
//	struct s_duke			dukeengine;
	t_binds					binds;
	int						to_be_drawn;
	void					(*draw)(struct s_engine*);
	char					picker;
}							t_engine;

void					engine(void);
void					draw_menu(t_engine *const eng);
void					draw_w3d(t_engine *const eng);
void					parse_w3d(t_engine *eng, char *path);
#endif
