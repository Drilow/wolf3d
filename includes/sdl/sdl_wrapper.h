/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_wrapper.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adleau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/11 14:35:49 by adleau            #+#    #+#             */
/*   Updated: 2018/01/18 14:05:24 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SDL_WRAPPER_H
# define SDL_WRAPPER_H
# define WIN_WD 640
# define WIN_HT 480
# include <SDL.h>

/* 2dvector
** x, y
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
	t_rect				wolf;
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
	SDL_Event			event;
}						t_sdl_wrapper;

void					init_sdl_wrap(t_sdl_wrapper *wrap);

#endif
