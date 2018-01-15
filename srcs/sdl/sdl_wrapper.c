/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_wrapper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adleau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/11 19:54:22 by adleau            #+#    #+#             */
/*   Updated: 2018/01/11 19:57:22 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <SDL2/SDL.h>
#include <sdl/sdl_wrapper.h>

void			init_sdl_wrap(t_sdl_wrapper *wrap)
{
	if (!(wrap->screen = SDL_CreateWindow("wolf3d", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIN_WD, WIN_HT)))
		exit(1);
}
