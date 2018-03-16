/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   detect_walls.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabessir <mabessir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 15:24:32 by mabessir          #+#    #+#             */
/*   Updated: 2018/03/16 15:45:47 by mabessir         ###   ########.fr       */
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
