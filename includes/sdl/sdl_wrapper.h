/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_wrapper.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adleau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/11 14:35:49 by adleau            #+#    #+#             */
/*   Updated: 2018/01/19 14:30:21 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SDL_WRAPPER_H
# define SDL_WRAPPER_H
# define WIN_WD 640
# define WIN_HT 480
# include <SDL.h>

typedef struct			s_color
{
	Uint8				r;
	Uint8				g;
	Uint8				b;
}						t_color;

/* 2DVECTOR
** X, y
 */

typedef struct			s_2dvector
{
	int					x;
	int					y;
}						t_2dvector;

/* Rectangle structure
** holds start and end of the rectangle
 */

typedef struct			s_rect
{
	t_2dvector			start;
	t_2dvector			end;
}						t_rect;

/* Menu wrapper
** holds infos to generate the menu screen
 */

typedef struct			s_menu
{
	t_rect				title;
	t_rect				w3d;
	t_rect				doom;
	t_rect				duke;
}						t_menu;

/* SDL_WRAPPER
** holds the data relevant to the SDL
 */

typedef struct			s_sdl_wrapper
{
	SDL_Window			*screen;
	t_menu				data;
	SDL_Surface			*menu;
	SDL_Surface			*wolf;
	SDL_Renderer		*renderer;
	SDL_Texture			*tex;
	SDL_Event			event;
}						t_sdl_wrapper;

void					init_sdl_wrap(t_sdl_wrapper *wrap);
void					init_menu_rectangles(t_menu *menu);
void					draw_rect(t_rect *rect, SDL_Surface *surf, int color);

#endif
