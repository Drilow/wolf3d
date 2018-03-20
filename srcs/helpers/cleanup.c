/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabessir <mabessir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/06 20:42:52 by adleau            #+#    #+#             */
/*   Updated: 2018/03/20 16:52:12 by mabessir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <SDL.h>
#include <SDL_image.h>
#include <helpers/cleanup.h>
#include <helpers/sdl_wrapper.h>
#include <mandatory_part/wolf.h>
#include "libft.h"

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
	if (i == 2)
		ft_putstr("Wrong path for map.\n");
	if (i == 3)
		ft_putstr("Wrong path for textures.\n");
	if (i == 4)
		ft_putstr("Wrong map format. Please verify the model.\n");
	if (i == 5)
		ft_putstr("Map is too big or too small. Be smart.\n");
	if (i == 6)
		ft_putstr("Something is wrong with map informations.\n");
	if (i == 7)
		ft_putstr("ERROR. Textures can only be selected between\
		0 - 5 for X and 0 - 17 for Y\n");
	if (i == 8)
		ft_putstr("Check Camera value. Be smart. Protips : 0 - 360\n");
	if (i == 9)
		ft_putstr("Something is wrong with map.\n");
	free_sdl_wrapper(wolf->wrap);
	free_map(&(wolf->map));
	exit(i);
}
