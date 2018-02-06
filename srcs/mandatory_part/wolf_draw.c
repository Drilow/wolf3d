/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf_draw.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adleau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 08:28:28 by adleau            #+#    #+#             */
/*   Updated: 2018/02/06 15:33:31 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <SDL.h>
#include <mandatory_part/wolf.h>
#include <mandatory_part/walls.h>
#include <mandatory_part/w3d_calc.h>

void			get_direction(t_vector_2d *direction, double ray)
{
	if (ray > 0 && ray <= 180)
		direction->x = 1;
	else if (ray > 180 && ray < 360)
		direction->x = -1;
	if (ray > 90 && ray <= 270)
		direction.y = 1;
	else if ((ray < 90 && ray >= 0) || (ray > 270 && ray < 360))
		direction.y = -1;
}

void			init_w3d_calc(t_w3dcalc *calc, t_w3dmap *map, double ray)
{
	get_direction(calc->direction, ray);
	calc->start.x = map->pos.x;
	calc->start.y = map->pos.y;
	calc->player.x = (calc->direction.x > 0) ? CELL - map->cam.player.x : map->cam.player.x;
	calc->player.y = (calc->direction.y > 0) ? CELL - map->cam.player.y : map->cam.player.y;
	calc->processed.x = 0;
	calc->processed.y = 0;
	calc->distance = 0;
}

int				round(double d)
{
	return ((d - (int)d >= .5) ? (int)d + 1 : (int)d);
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

void			launch_ray(t_wall *wall, t_w3dmap *map, double ray, int i)
{
	t_w3dcalc	calc;
	t_vector_2d	first;

	init_w3d_calc(&calc, map, ray);
	ray = get_angle(ray);
	while (!was_wall_hit(&(calc), map->map, x_checker) ||)
}

int				compare_vector_2d(t_vector_2d v1, t_vector_2d v2)
{
	if (v1.x == v2.x && v1.y == v2.y)
		return (0);
	return (1);
}

int				launch_rays(t_wall *wall, t_wolf *wolf, double *rays, double inc)
{
	int			i;
	t_vector_2d	start;

	i= 1;
	if (!(wall->collumns = (int*)malloc(sizeof(int*))))
		free_wolf(wolf, 1);
	wall->collumns[0] = launch_ray(wall, &(wolf->map), *rays);
	start = wall->inmap;
	*rays += inc;
	while (!compare_vector_2d(wall->inmap, start))
	{
		launch_ray(wall, &(wolf->map), *rays, i);
		*rays += inc;
		i++;
	}
	return (i);
}

/* init_wall function
** initializes the wall structure for the drawing
 */

void		init_wall(t_wall *wall)
{
	wall->left.start = -1;
	wall->left.end = -1;
	wall->right.start = -1;
	wall->right.end = -1;
	wall->collumns = NULL;
	wall->current = -1;
	wall->direction.x = 0;
	wall->direction.y = 0;
}

/* w3d_draw function
** entry point of the drawing module
 */

void		w3d_draw(t_wolf *wolf)
{
	double	rays;
	double	inc;
	int		x;
	t_wall	wall;

	x = -1;
	rays = wolf->map.cam.range[0];
	inc = rays / WIN_WD;
	init_wall(&wall);
	while (++x < WIN_WD && rays <= wolf->map.cam.range[1])
	{
		if (!wall.collumns)
			x += launch_rays(&wall, wolf, &rays, inc);
		draw_wall(wolf->wrap->wolf, pick_wall(wall.direction, wolf->map.walls), wall.current, wall);
		free(wall.collumns);
		init_wall(&wall);
	}
	SDL_RenderClear(wolf->wrap->renderer);
	SDL_RenderCopy(wolf->wrap->renderer, wolf->wrap->tex, NULL, NULL);
	SDL_RenderPresent(wolf->wrap->renderer);
}
