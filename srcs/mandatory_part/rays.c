/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabessir <mabessir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 15:11:19 by mabessir          #+#    #+#             */
/*   Updated: 2018/03/16 15:16:53 by mabessir         ###   ########.fr       */
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
