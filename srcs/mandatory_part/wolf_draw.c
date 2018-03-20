/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf_draw.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabessir <mabessir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 08:28:28 by adleau            #+#    #+#             */
/*   Updated: 2018/03/20 10:05:42 by mabessir         ###   ########.fr       */
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
	if (walls->wall->start > 0)
		walls->collumns[walls->wall->start] =
		walls->collumns[walls->wall->start - 1];
	if (!(walls->wall->next = (t_wall*)malloc(sizeof(t_wall))))
		free_wolf(wolf, 1);
	walls->wall = walls->wall->next;
	init_wall(walls->wall);
}

void				sdl_handle(t_sdl_wrapper *wrap)
{
	SDL_RenderClear(wrap->renderer);
	SDL_RenderCopy(wrap->renderer, wrap->tex, NULL, NULL);
	SDL_RenderPresent(wrap->renderer);
	SDL_DestroyTexture(wrap->tex);
	wrap->tex = NULL;
}
