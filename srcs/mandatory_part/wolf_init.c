/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adleau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 08:24:39 by adleau            #+#    #+#             */
/*   Updated: 2018/02/05 11:32:19 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <full_run.h>
#include <mandatory_part/wolf.h>
#include <helpers/cleanup.h>
#include <helpers/str_helpers.h>
#include <fcntl.h>
#include <SDL.h>
#include <SDL_image.h>

void		init_w3dparse(t_wolf *wolf, char *path)
{
	if (path == NULL)
		if (!(path = ft_strdup("maps/wolf3d/lvl1.w3dmap")))
			free_wolf(wolf, 1);
	if ((wolf->parse.fd = open(path, O_RDONLY)) == -1)
		free_wolf(wolf, 1);
	wolf->parse.beenread = -1;
	wolf->parse.linesread = -1;
	wolf->parse.done = 0;
}

void		init_w3dmap(t_wolf *wolf, t_w3dmap *map)
{
	map->map = NULL;
	map->size.x = 0;
	map->size.y = 0;
	map->pos.x = -1;
	map->pos.y = -1;
//	init_w3dcam(&(map->cam));
	if (!(map->walls = (SDL_Surface**)malloc(sizeof(SDL_Surface*) * 4)))
		free_wolf(wolf, 1);
}

/* init_wolf function
** initializes all the data relative to the w3d wolfine
*/

void		init_wolf(t_wolf *wolf, t_sdl_wrapper *wrap, char *path)
{
	init_w3dparse(wolf, path);
	init_w3dmap(wolf, &(wolf->map));
	wrap->drawn = 0;
	w3d_parse(wolf);
}