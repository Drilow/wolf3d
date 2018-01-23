/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_w3d.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adleau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/21 15:53:28 by adleau            #+#    #+#             */
/*   Updated: 2018/01/23 15:43:44 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <SDL.h>
#include <SDL_image.h>
#include <engine/engine.h>
#include <draw/draw.h>
#include <cleanup/cleanup.h>
#include <w3d/map.h>
#include <draw/raycaster.h>

/* init_wall_surfaces
** loads the wall textures
 */

void			init_wall_surfaces(t_engine *eng, t_w3dmap *map)
{
	int			i;

	i = -1;
	if (!map->wall_surf)
	{
		if (!(map->wall_surf = (SDL_Surface**)malloc(sizeof(SDL_Surface*) * 4)))
			free_everything(eng, 1);
		while (++i < 4)
		{
			if (!(map->wall_surf[i] = SDL_CreateRGBSurfaceWithFormat(0, WIN_WD, WIN_HT, 32, SDL_PIXELFORMAT_RGBA32)))
			{
				printf("%s\n", SDL_GetError());
				free_everything(eng, 1);
			}
			if (!(map->wall_surf[i] = IMG_Load(map->walls[i])))
			{
				printf("2 %s\n", SDL_GetError());
				free_everything(eng, 1);
			}
		}
		printf("chatte\n");
	}
}

/* init_starting_pos
** places the player on the starting point (S)
 */

void			init_starting_pos(t_engine *eng, t_w3dmap *map)
{
	int			r;

	r = 0;
	map->pos.y = -1;
	while (!r && ++(map->pos.y) < map->size.x)
	{
		map->pos.x = -1;
		while (++(map->pos.x) < map->size.x)
			if (map->map_tab[map->pos.y][map->pos.x] == 'S')
			{
				r = 1;
				break ;
			}
	}
	map->camera.fov = 60;
	if (map->pos.x == map->size.x && map->pos.y == map->size.y)
		free_everything(eng, 1);
}

/* init_w3dmap function
** inits the parameters relevant to the w3dmap
*/

void			init_w3dmap(t_engine *eng, t_w3dmap *map)
{
	init_wall_surfaces(eng, map);
	init_starting_pos(eng, map);
}

/* draw_w3d function
** entry point to the wolf3d engine
 */

void			draw_w3d(t_engine *const eng)
{
	if (eng->parser.map.pos.x == -1 && eng->parser.map.pos.y == -1)
		init_w3dmap(eng, &(eng->parser.map));
	raycaster(eng);
	if (!(eng->mainwindow.tex = SDL_CreateTextureFromSurface(eng->mainwindow.renderer, eng->mainwindow.wolf)))
	{
		printf("%s\n", SDL_GetError());
		free_everything(eng, 1);
	}
	SDL_RenderClear(eng->mainwindow.renderer);
	SDL_RenderCopy(eng->mainwindow.renderer, eng->mainwindow.tex, NULL, NULL);
	SDL_RenderPresent(eng->mainwindow.renderer);
	eng->to_be_drawn = 1;
}
