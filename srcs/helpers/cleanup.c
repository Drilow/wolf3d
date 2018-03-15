/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adleau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/06 20:42:52 by adleau            #+#    #+#             */
/*   Updated: 2018/03/15 15:18:43 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <SDL.h>
#include <SDL_image.h>
#include <helpers/cleanup.h>
#include <helpers/sdl_wrapper.h>
#include <mandatory_part/wolf.h>

/*
** free_sdl_wrapper
** frees everything SDL-related
*/

void			free_sdl_wrapper(t_sdl_wrapper *sdl_wrap)
{
	if (sdl_wrap->screen)
		SDL_DestroyWindow(sdl_wrap->screen);
	if (sdl_wrap->wolf)
		SDL_FreeSurface(sdl_wrap->wolf);
	if (sdl_wrap->renderer)
		SDL_DestroyRenderer(sdl_wrap->renderer);
	if (sdl_wrap->tex)
		SDL_DestroyTexture(sdl_wrap->tex);
	if (sdl_wrap)
		free((t_sdl_wrapper*)sdl_wrap);
	SDL_Quit();
	IMG_Quit();
}

void			free_wall(t_wall *wall)
{
	if (wall)
		free_wall(wall->next);
	free((t_wall*)wall);
}

void			free_walls(t_walls *walls)
{
	if (walls->collumns)
		free((int*)walls->collumns);
	free_wall(walls->wall);
}

void			free_map(t_w3dmap *map)
{
	int			i;

	i = -1;
	if (map->map)
	{
		while (++i < map->size.y)
			free((char*)map->map[i]);
		free((char**)map->map);
	}
	if (map->textures)
		SDL_FreeSurface(map->textures);
}

void			free_wolf(t_wolf *wolf, int i)
{
	free_sdl_wrapper(wolf->wrap);
	free_map(&(wolf->map));
	exit(i);
}
