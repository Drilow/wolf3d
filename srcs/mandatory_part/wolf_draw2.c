/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf_draw2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabessir <mabessir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 15:26:17 by mabessir          #+#    #+#             */
/*   Updated: 2018/03/22 11:04:03 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <SDL.h>
#include <libft.h>
#include <mandatory_part/wolf.h>
#include <mandatory_part/walls.h>
#include <mandatory_part/w3d_calc.h>
#include <helpers/cleanup.h>
#include <mandatory_part/w3d_rays.h>

#define OFF_Y w_ray.off.y
#define OFF_X w_ray.off.x
#define POFF_Y w_ray->off.y
#define POFF_X w_ray->off.x
#define P_MAP_X w_ray->inmap.x
#define P_MAP_Y w_ray->inmap.y
#define PROCX_Y w_ray.inmap.y + (w_ray.dir.y * (OFF_Y + w_ray.proc_x.y) / CELL)
#define PROCX_X w_ray.inmap.x + (w_ray.dir.x * (OFF_X + w_ray.proc_x.x) / CELL)
#define PROCY_Y w_ray.inmap.y + (w_ray.dir.y * (OFF_Y + w_ray.proc_y.y) / CELL)
#define PROCY_X w_ray.inmap.x + (w_ray.dir.x * (OFF_X + w_ray.proc_y.x) / CELL)
#define PPROCX_Y (P_MAP_Y + (w_ray->dir.y * (POFF_Y + w_ray->proc_x.y) / CELL))
#define PPROCX_X (P_MAP_X + (w_ray->dir.x * (POFF_X + w_ray->proc_x.x) / CELL))
#define PPROCY_Y (P_MAP_Y + (w_ray->dir.y * (POFF_Y + w_ray->proc_y.y) / CELL))
#define PPROCY_X (P_MAP_X + (w_ray->dir.x * (POFF_X + w_ray->proc_y.x) / CELL))

t_vector_2d			get_player(t_vector_2d player, t_vector_2d direction)
{
	t_vector_2d		ret;

	ret.x = (direction.x == 1) ? player.x : CELL - player.x;
	ret.y = (direction.y == 1) ? player.y : CELL - player.y;
	return (ret);
}

void				init_ray(t_wolf *wolf, t_w3dray *w_ray, double c_ray)
{
	w_ray->orientation = c_ray;
	w_ray->angle = get_angle(c_ray);
	w_ray->tanner = tan(w_ray->angle * M_PI / 180);
	get_direction(&(w_ray->dir), c_ray);
	w_ray->inmap.x = wolf->map.pos.x;
	w_ray->inmap.y = wolf->map.pos.y;
	w_ray->off = get_player(wolf->map.cam.player, w_ray->dir);
	w_ray->proc_x.x = 0;
	w_ray->proc_x.y = 0;
	w_ray->proc_y.x = 0;
	w_ray->proc_y.y = 0;
	w_ray->hit.x = 0;
	w_ray->hit.y = 0;
	w_ray->distance.x = 0;
	w_ray->distance.y = 0;
}

void				init_draw(t_wolf *wolf, t_walls *walls)
{
	draw_floor_ceiling(wolf->wrap->wolf,
	wolf->map.textures, &(wolf->map.background));
	init_w3dcam(&(wolf->map.cam));
	if (init_walls(walls))
		free_wolf(wolf, 1);
	if (wolf->wrap->tex)
	{
		SDL_DestroyTexture(wolf->wrap->tex);
		wolf->wrap->tex = NULL;
	}
	draw_loop(wolf, walls);
}

void				draw_loop(t_wolf *wolf, t_walls *walls)
{
	int				x;
	double			rays;
	double			inc;
	t_wall			*start;

	start = NULL;
	rays = wolf->map.cam.range[0];
	inc = wolf->map.cam.fov / WIN_WD;
	x = -1;
	while (++x <= WIN_WD)
	{
		if (rays >= 360 || rays < 0)
			rays += (rays >= 360) ? -360 : 360;
		x = handle_90degrees(walls, x, &rays, &inc);
		walls->wall->inmap = detect_wall(wolf, walls->wall, rays, x);
		walls->collumns[x] = walls->wall->col;
		if (walls->collumns[x] <= 0 && x != 0)
			walls->collumns[x] = walls->collumns[x - 1];
		if (!start)
			start = walls->wall;
		else if (walls->wall->end >= 0)
			last_if(wolf, walls);
		rays += inc;
	}
	walls->wall = start;
}

void				w3d_draw(t_wolf *wolf)
{
	t_walls			walls;
	t_wall			*start;

	init_draw(wolf, &walls);
	start = walls.wall;
	if (walls.wall->end == -1 && walls.wall->start != -1)
		walls.wall->end = WIN_WD;
	walls_loop(wolf, &walls);
	walls.wall = start;
	free_walls(&walls);
	if (!(wolf->wrap->renderer))
		if (!(wolf->wrap->renderer = SDL_CreateRenderer(wolf->wrap->screen,
		-1, SDL_RENDERER_ACCELERATED)))
			free_wolf(wolf, 1);
	if (!(wolf->wrap->tex))
		if (!(wolf->wrap->tex =
		SDL_CreateTextureFromSurface(wolf->wrap->renderer, wolf->wrap->wolf)))
			free_wolf(wolf, 1);
	sdl_handle(wolf->wrap);
}
