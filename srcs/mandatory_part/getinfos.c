/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getinfos.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabessir <mabessir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 16:00:22 by mabessir          #+#    #+#             */
/*   Updated: 2018/03/16 16:00:43 by mabessir         ###   ########.fr       */
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

int					get_dist(t_vector_2d *proc)
{
	return (sqrt(pow(proc->x, 2) + pow(proc->y, 2)));
}
