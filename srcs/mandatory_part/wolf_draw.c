/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf_draw.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adleau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 08:28:28 by adleau            #+#    #+#             */
/*   Updated: 2018/02/15 12:16:50 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <SDL.h>
#include <libft.h>
#include <mandatory_part/wolf.h>
#include <mandatory_part/walls.h>
#include <mandatory_part/w3d_calc.h>
#include <helpers/cleanup.h>
#include <mandatory_part/w3d_rays.h>

#define PROCX_Y w_ray.inmap.y + (w_ray.direction.y * (w_ray.off.y + w_ray.proc_x.y) / CELL)
#define PROCX_X w_ray.inmap.x + (w_ray.direction.x * (w_ray.off.x + w_ray.proc_x.x) / CELL)
#define PROCY_Y w_ray.inmap.y + (w_ray.direction.y * (w_ray.off.y + w_ray.proc_y.y) / CELL)
#define PROCY_X w_ray.inmap.x + (w_ray.direction.x * (w_ray.off.x + w_ray.proc_y.x) / CELL)
#define PPROCX_Y w_ray->inmap.y + (w_ray->direction.y * (w_ray->off.y + w_ray->proc_x.y) / CELL)
#define PPROCX_X w_ray->inmap.x + (w_ray->direction.x * (w_ray->off.x + w_ray->proc_x.x) / CELL)
#define PPROCY_Y w_ray->inmap.y + (w_ray->direction.y * (w_ray->off.y + w_ray->proc_y.y) / CELL)
#define PPROCY_X w_ray->inmap.x + (w_ray->direction.x * (w_ray->off.x + w_ray->proc_y.x) / CELL)

int				compare_vector_2d(t_vector_2d v1, t_vector_2d v2)
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
	wall->first_proc = -1;
	wall->processed_size = -1;
	wall->col = 0;
	wall->direction.x = 0;
	wall->direction.y = 0;
	wall->inmap.x = -1;
	wall->inmap.y = -1;
	wall->next = NULL;
}

int					init_walls(t_walls *walls)
{
	walls->collumns = NULL;
	if (!(walls->collumns = (int*)malloc(sizeof(int) * (WIN_WD + 1))))
		return (1);
	ft_bzero((void*)walls->collumns, WIN_WD + 1);
	walls->wall = NULL;
	if (!(walls->wall = (t_wall*)malloc(sizeof(t_wall))))
		return (1);
	init_wall(walls->wall);
	return (0);
}

double			get_angle(double d)
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

SDL_Surface		*pick_wall(SDL_Surface **walls, t_vector_2d dir)
{
	int			i;

	i = 0;
	if (dir.x == -1 && dir.y == -1)
		i = 0;
	if (dir.x == -1 && dir.y == 1)
		i = 1;
	if (dir.x == 1 && dir.y == -1)
		i = 2;
	if (dir.x == 1 && dir.y == 1)
		i = 3;
	return (walls[i]);
}

void			get_direction(t_vector_2d *direction, double ray)
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
	get_direction(&(w_ray->direction), c_ray);
	w_ray->inmap.x = wolf->map.pos.x;
	w_ray->inmap.y = wolf->map.pos.y;
	w_ray->off = get_player(wolf->map.cam.player, w_ray->direction);
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

void				launch_ray(t_w3dray *w_ray, t_vector_2d *size)
{
	if (w_ray->proc_x.x == 0 && w_ray->proc_y.y == 0)
	{
		w_ray->proc_x.y = CELL - w_ray->off.y;
		if (PPROCX_X < size->x)
			w_ray->proc_x.x = w_ray->proc_x.y / w_ray->tanner;
		w_ray->proc_y.x = CELL - w_ray->off.x;
		if (PPROCY_Y < size->y - 1)
			w_ray->proc_y.y = w_ray->proc_y.x * w_ray->tanner;
	}
	else
	{
		if (!(w_ray->distance.x))
		{
			w_ray->proc_x.y += CELL;
			if (PPROCX_X < size->x)
				w_ray->proc_x.x = w_ray->proc_x.y / w_ray->tanner;
		}
		if (!(w_ray->distance.y))
		{
			w_ray->proc_y.x += CELL;
			if (PPROCY_Y < size->y - 1)
				w_ray->proc_y.y = w_ray->proc_y.x * w_ray->tanner;
		}
	}
}

void				handle_overflow(t_w3dray *w_ray, t_vector_2d size)
{
	if (PPROCX_X >= size.x || PPROCX_X < 0)
	{
		while (PPROCX_X >= size.x || PPROCX_X < 0)
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

t_vector_2d			detect_wall(t_wolf *wolf, t_wall *wall, double c_ray, int x)
{
	t_w3dray		w_ray;

	init_ray(wolf, &w_ray, c_ray);
	if (wall->inmap.x < 0 && wall->inmap.y < 0)
		wall->start = x;
	while (w_ray.angle != 90 && (w_ray.distance.x == 0 || w_ray.distance.y == 0))
	{
		if (PROCX_Y >= 0 && PROCX_X >= 0 && PROCX_Y < wolf->map.size.y && PROCX_X < wolf->map.size.x)
			if ((wolf->map.map[PROCX_Y][PROCX_X] != '0') &&
			(wolf->map.map[PROCX_Y][PROCX_X] != 'S'))
				w_ray.distance.x = get_dist(&(w_ray.proc_x));
		if (PROCY_Y >= 0 && PROCY_X >= 0 && PROCY_Y < wolf->map.size.y && PROCY_X < wolf->map.size.x)
			if ((wolf->map.map[PROCY_Y][PROCY_X] != '0') &&
			(wolf->map.map[PROCY_Y][PROCY_X] != 'S'))
				w_ray.distance.y = get_dist(&(w_ray.proc_y));
		handle_overflow(&w_ray, wolf->map.size);
		launch_ray(&w_ray, &(wolf->map.size));
	}
	w_ray.inmap.x = (w_ray.distance.x < w_ray.distance.y) ? PROCX_X : PROCY_X;
	w_ray.inmap.y = (w_ray.distance.x < w_ray.distance.y) ? PROCX_Y : PROCY_Y;
	if (wall->inmap.x >= 0 && wall->inmap.y >= 0)
	{
		if (wall->start == x)
			wall->first_proc = (w_ray.distance.x < w_ray.distance.y) ? w_ray.proc_x.x : w_ray.proc_y.y;
		if (compare_vector_2d(w_ray.inmap, wall->inmap))
		{
			wall->end = x;
			wall->processed_size = CELL - wall->first_proc;
			wall->l_off = (wall->first_proc * CELL) / wall->processed_size;
			wall->direction.x = w_ray.direction.x;
			wall->direction.y = w_ray.direction.y;
		}
		else
			wall->col = (w_ray.distance.x < w_ray.distance.y) ? CELL / w_ray.distance.x * wolf->map.cam.screendist : CELL / w_ray.distance.y * wolf->map.cam.screendist; // wrong formula it seems
}
	return (w_ray.inmap);
}

void				w3d_draw(t_wolf *wolf)
{
	int				x;
	t_walls			walls;
	t_wall			*start;
	double			rays;
	double			inc;

	if (init_walls(&walls))
		free_wolf(wolf, 1);
	x = -1;
	start = walls.wall;
	rays = wolf->map.cam.range[0];
	inc = wolf->map.cam.fov / WIN_WD;
	while (++x <= WIN_WD) // raycast loop
	{
		if (walls.wall->start < 0)
		{
			walls.wall->inmap = detect_wall(wolf, walls.wall, rays, x);
		}
		else if (walls.wall->end >= 0)
		{
			if (!(walls.wall->next = (t_wall*)malloc(sizeof(t_wall))))
				free_wolf(wolf, 1);
			walls.wall = walls.wall->next;
			init_wall(walls.wall);
		}
		if (walls.wall != NULL)
			walls.wall->inmap = detect_wall(wolf, walls.wall, rays, x);
		walls.collumns[x] = walls.wall->col;
		rays += inc;
	}
	walls.wall = start;
	while (walls.wall)
	{
		printf("prout %d %d\n", walls.wall->end,  walls.collumns[walls.wall->end - 1]);
		draw_wall(wolf->wrap->wolf, pick_wall(wolf->map.walls, walls.wall->direction), walls.collumns, walls.wall);
		walls.wall = walls.wall->next;
	}
	printf("out\n");
	exit(1);
}
