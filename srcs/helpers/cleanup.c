/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adleau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/06 20:42:52 by adleau            #+#    #+#             */
/*   Updated: 2018/03/08 12:27:22 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <SDL.h>
#include <SDL_image.h>
#include <helpers/cleanup.h>
#include <helpers/sdl_wrapper.h>
#include <mandatory_part/wolf.h>

/* free_sdl_wrapper
** frees everything SDL-related
 */

void			free_sdl_wrapper(t_sdl_wrapper *sdl_wrap)
{
	if (sdl_wrap->screen)
		SDL_DestroyWindow(sdl_wrap->screen);
	if (sdl_wrap->menu)
		SDL_FreeSurface(sdl_wrap->menu);
	if (sdl_wrap->wolf)
		SDL_FreeSurface(sdl_wrap->wolf);
	if (sdl_wrap->renderer)
		SDL_DestroyRenderer(sdl_wrap->renderer);
	if (sdl_wrap->tex)
		SDL_DestroyTexture(sdl_wrap->tex);
	SDL_Quit();
	IMG_Quit();
}

void			free_wolf(t_wolf *wolf, int i)
{
	free_sdl_wrapper(wolf->wrap);
	if (wolf->map.textures)
		SDL_FreeSurface(wolf->map.textures);
	exit(i);
}
