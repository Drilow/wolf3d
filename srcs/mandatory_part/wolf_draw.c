/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf_draw.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabessir <mabessir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 08:28:28 by adleau            #+#    #+#             */
/*   Updated: 2018/03/14 14:42:15 by adleau           ###   ########.fr       */
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

int					compare_vector_2d(t_vector_2d v1, t_vector_2d v2)
{
	if (v1.x == v2.x && v1.y == v2.y)
		return (0);
	return (1);
}

void				init_wall(t_wall *wall)
{
	wall->start = -1;
	wall->end = -1;
	wall->l_off = -1;
	wall->processed_size = -1;
	wall->col = 0;
	wall->direction.x = 0;
	wall->direction.y = 0;
	wall->inmap.x = -1;
	wall->inmap.y = -1;
	wall->next = NULL;
	wall->orientation = 0;
	wall->flag = -1;
	wall->detected = -1;
}

int					init_walls(t_walls *walls)
{
	walls->collumns = NULL;
	if (!(walls->collumns = (int*)malloc(sizeof(int) * (WIN_WD + 1))))
		return (1);
	ft_bzero(walls->collumns, WIN_WD + 1);
	walls->wall = NULL;
	if (!(walls->wall = (t_wall*)malloc(sizeof(t_wall))))
		return (1);
	init_wall(walls->wall);
	return (0);
}

double				get_angle(double d)
{
	double		r;

	r = 0;
	if (d < 90)
		r = 90 - d;
	else if (d < 180)
		r = d - 90;
	else if (d < 270)
		r = 270 - d;
	else if (d < 360)
		r = d - 270;
	return (r);
}

int					pick_wall(t_wall *wall)
{
	int			i;

	i = 0;
	if (wall->direction.y == -1 && (wall->direction.x == -1
	|| wall->direction.x == 1) && wall->detected == 1)
		i = 0;
	else if (wall->direction.x == 1 && (wall->direction.y == -1
	|| wall->direction.y == 1) && wall->detected == 0)
		i = 1;
	else if (wall->direction.y == 1 && (wall->direction.x == -1
	|| wall->direction.x == 1) && wall->detected == 1)
		i = 2;
	else if (wall->direction.x == -1 && (wall->direction.y == -1
	|| wall->direction.y == 1) && wall->detected == 0)
		i = 3;
	return (i);
}

void				get_direction(t_vector_2d *direction, double ray)
{
	if (ray > 0 && ray <= 180)
		direction->x = 1;
	else if (ray > 180 && ray < 360)
		direction->x = -1;
	if (ray > 90 && ray <= 270)
		direction->y = 1;
	else if ((ray < 90 && ray >= 0) || (ray > 270 && ray < 360))
		direction->y = -1;
}

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

int					get_dist(t_vector_2d *proc)
{
	return (sqrt(pow(proc->x, 2) + pow(proc->y, 2)));
}

void				launch_xray(t_w3dray *w_ray, t_vector_2d *size)
{
	w_ray->proc_x.y = CELL - w_ray->off.y;
	if (PPROCX_X >= 0 && PPROCX_X < size->x)
	{
		w_ray->proc_x.x = (int)((double)w_ray->proc_x.y / w_ray->tanner);
		w_ray->hit.x = 1;
	}
	w_ray->proc_y.x = CELL - w_ray->off.x;
	if (PPROCY_Y >= 0 && PPROCY_Y < size->y)
	{
		w_ray->proc_y.y = (int)((double)w_ray->proc_y.x * w_ray->tanner);
		w_ray->hit.y = 1;
	}
}

void				launch_ray(t_w3dray *w_ray, t_vector_2d *size)
{
	if (!(w_ray->hit.x) && !(w_ray->hit.y))
		launch_xray(w_ray, size);
	else
	{
		if (!(w_ray->distance.x))
		{
			w_ray->proc_x.y += CELL;
			if (PPROCX_X && PPROCX_X < size->x)
				w_ray->proc_x.x = w_ray->proc_x.y / w_ray->tanner;
		}
		if (!(w_ray->distance.y))
		{
			w_ray->proc_y.x += CELL;
			if (PPROCY_Y && PPROCY_Y < size->y)
				w_ray->proc_y.y = w_ray->proc_y.x * w_ray->tanner;
		}
	}
}

void				handle_overflow(t_w3dray *w_ray, t_vector_2d size)
{
	if (PPROCX_X >= size.x || PPROCX_X < 0)
	{
		while (PPROCX_X >= size.x)
			w_ray->proc_x.x -= CELL;
		w_ray->distance.x = get_dist(&(w_ray->proc_x));
	}
	if (PPROCY_Y >= size.y || PPROCY_Y < 0)
	{
		while (PPROCY_Y >= size.y || PPROCY_Y < 0)
			w_ray->proc_y.y -= CELL;
		w_ray->distance.y = get_dist(&(w_ray->proc_y));
	}
}

void				detect_wall2(t_wolf *wolf, t_w3dray w_ray,
t_wall *wall, double c_ray)
{
	if ((compare_vector_2d(w_ray.inmap, wall->inmap) ||
	(wall->flag != -1 && wall->detected != -1 && wall->flag
	!= wall->detected)) || wolf->x == WIN_WD)
		wall->end = wolf->x;
	wall->col = (w_ray.distance.x < w_ray.distance.y) ?
	(int)round((CELL / (double)w_ray.distance.x)
	* wolf->map.cam.screendist * 2 / 3) : (int)round((CELL /
	(double)w_ray.distance.y) * wolf->map.cam.screendist * 2 / 3);
	wall->col /= cos(fabs(wolf->map.cam.orientation - c_ray) * M_PI / 180);
}

void				wall_loop(t_wolf *wolf, t_w3dray *w_ray)
{
	while ((w_ray->distance.x == 0 || w_ray->distance.y == 0))
	{
		if (PPROCX_Y >= 0 && PPROCX_X >= 0 && PPROCX_Y
			< wolf->map.size.y && PPROCX_X < wolf->map.size.x)
		{
			if ((wolf->map.map[PPROCX_Y][PPROCX_X] != '0') &&
				(wolf->map.map[PPROCX_Y][PPROCX_X] != 'S'))
				w_ray->distance.x = get_dist(&(w_ray->proc_x));
		}
		if (PPROCY_Y >= 0 && PPROCY_X >= 0 && PPROCY_Y
			< wolf->map.size.y && PPROCY_X < wolf->map.size.x)
		{
			if ((wolf->map.map[PPROCY_Y][PPROCY_X] != '0') &&
				(wolf->map.map[PPROCY_Y][PPROCY_X] != 'S'))
				w_ray->distance.y = get_dist(&(w_ray->proc_y));
		}
		handle_overflow(w_ray, wolf->map.size);
		launch_ray(w_ray, &(wolf->map.size));
	}
}

t_vector_2d			detect_wall(t_wolf *wolf,
t_wall *wall, double c_ray, int x)
{
	t_w3dray		w_ray;

	init_ray(wolf, &w_ray, c_ray);
	wall->detected = wall->flag;
	if (wall->inmap.x < 0 && wall->inmap.y < 0)
		wall->start = x;
	wall_loop(wolf, &w_ray);
	w_ray.inmap.x =
	(w_ray.distance.x < w_ray.distance.y) ? PROCX_X : PROCY_X;
	w_ray.inmap.y =
	(w_ray.distance.x < w_ray.distance.y) ? PROCX_Y : PROCY_Y;
	wall->direction.x = w_ray.dir.x;
	wall->direction.y = w_ray.dir.y;
	wall->flag = (w_ray.distance.x < w_ray.distance.y) ? 1 : 0;
	if (w_ray.distance.x == w_ray.distance.y)
		wall->flag = wall->detected;
	if (wall->inmap.x >= 0 && wall->inmap.y >= 0)
	{
		wolf->x = x;
		detect_wall2(wolf, w_ray, wall, c_ray);
	}
	return (w_ray.inmap);
}

int					handle_90degrees(t_walls *walls, int x,
					double *rays, double *inc)
{
	if (*rays == 90)
	{
		if (x)
			walls->collumns[x] = walls->collumns[x - 1];
		else
			walls->collumns[x] = 0;
		*rays += *inc;
		return (x++);
	}
	return (x);
}

void				last_if(t_wolf *wolf, t_walls *walls)
{
	walls->collumns[walls->wall->start] =
		walls->collumns[walls->wall->start - 1];
	if (!(walls->wall->next = (t_wall*)malloc(sizeof(t_wall))))
		free_wolf(wolf, 1);
	walls->wall = walls->wall->next;
	init_wall(walls->wall);
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
		if (walls->collumns[x] <= 0)
			walls->collumns[x] = walls->collumns[x - 1];
		if (!start)
			start = walls->wall;
		else if (walls->wall->end >= 0)
			last_if(wolf, walls);
		rays += inc;
	}
	walls->wall = start;
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

void				sdl_handle(t_sdl_wrapper *wrap)
{
	SDL_RenderClear(wrap->renderer);
	SDL_RenderCopy(wrap->renderer, wrap->tex, NULL, NULL);
	SDL_RenderPresent(wrap->renderer);
	SDL_DestroyTexture(wrap->tex);
	wrap->tex = NULL;
}

void				w3d_draw(t_wolf *wolf)
{
	t_walls			walls;

	init_draw(wolf, &walls);
	if (walls.wall->end == -1 && walls.wall->start != -1)
		walls.wall->end = WIN_WD;
	while (walls.wall)
	{
		walls.wall->index = wolf->map.walltab[pick_wall(walls.wall)];
		if (walls.wall->start != -1 && walls.wall->end
			!= -1 && walls.wall->start - walls.wall->end != 0)
			draw_wall_tmp(wolf, &walls);
		else if (walls.wall->start == -1 || walls.wall->end == -1)
			break ;
		walls.wall = walls.wall->next;
	}
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
