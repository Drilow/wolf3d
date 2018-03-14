/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_wrapper.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabessir <mabessir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/11 14:35:49 by adleau            #+#    #+#             */
/*   Updated: 2018/03/14 12:17:49 by mabessir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SDL_WRAPPER_H
# define SDL_WRAPPER_H
# define WIN_WD 1280
# define WIN_HT 720
# include <SDL.h>

/*
** SDL_WRAPPER
** holds the data relevant to the SDL
*/

typedef struct			s_sdl_wrapper
{
	int					drawn;
	SDL_Window			*screen;
	SDL_Surface			*wolf;
	SDL_Renderer		*renderer;
	SDL_Texture			*tex;
	SDL_Event			event;
}						t_sdl_wrapper;

void					init_sdl_wrap(t_sdl_wrapper *wrap);

#endif
