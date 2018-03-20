/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabessir <mabessir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 08:24:39 by adleau            #+#    #+#             */
/*   Updated: 2018/03/20 16:17:39 by mabessir         ###   ########.fr       */
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
#include <math.h>

void		init_w3dcam(t_w3d_camera *cam)
{
	cam->fov = 60;
	cam->screendist = WIN_WD / 2 / tan(cam->fov / 2 * M_PI / 180);
	cam->angle = get_angle(cam->orientation);
	cam->range[0] = cam->orientation - cam->fov / 2;
	cam->range[1] = cam->orientation + cam->fov / 2;
	cam->direction.x = 0;
	cam->direction.y = 0;
	get_direction(&(cam->direction), cam->orientation);
}

void		init_w3dparse(t_wolf *wolf, char *path)
{
	int		i;

	i = 0;
	if (path == NULL)
	{
		if (!(path = ft_strdup("maps/wolf3d/lvl2.w3dmap")))
			free_wolf(wolf, 2);
		i = 1;
	}
	if ((wolf->parse.fd = open(path, O_RDONLY)) < 0)
		free_wolf(wolf, 1);
	wolf->parse.beenread = -1;
	wolf->parse.linesread = -1;
	wolf->parse.done = 0;
	wolf->parse.buf = NULL;
	if (i && path != NULL)
		free(path);
}

void		init_w3dmap(t_wolf *wolf, t_w3dmap *map)
{
	wolf->i = 0;
	wolf->spawn = 0;
	map->map = NULL;
	map->j = 0;
	map->size.x = 0;
	map->size.y = 0;
	map->pos.x = -1;
	map->pos.y = -1;
	if (!(map->textures = IMG_Load("assets/textures/default/1375.png")))
		free_wolf(wolf, 3);
	map->background.x = 1;
	map->background.y = 5;
	map->cam.player.x = CELL / 2;
	map->cam.player.y = CELL / 2;
	map->cam.orientation = 0;
}

/*
** init_wolf function
** initializes all the data relative to the w3d wolfine
*/

void		init_wolf(t_wolf *wolf, t_sdl_wrapper *wrap,
char *path)
{
	init_w3dparse(wolf, path);
	wrap->drawn = 0;
	init_w3dmap(wolf, &(wolf->map));
	w3d_parse(wolf);
	if (wolf->map.j != 4)
		free_wolf(wolf, 1);
	init_w3dcam(&(wolf->map.cam));
}
