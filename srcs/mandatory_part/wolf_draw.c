/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf_draw.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adleau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 08:28:28 by adleau            #+#    #+#             */
/*   Updated: 2018/02/06 11:16:40 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <SDL.h>
#include <mandatory_part/wolf.h>
#include <mandatory_part/walls.h>
#include <mandatory_part/w3d_calc.h>

void			init_w3d_calc(t_w3dcalc *calc, t_vector_2d pos)
{
	calc->x.inmap.x = map->pos.x;
	calc->x.inmap.y = map->pos.y;
	calc->y.inmap.x = map->pos.x;
	calc->y.inmap.y = map->pos.y;
	calc->x.x_dist = 0;
	calc->x.y_dist = 0;
	calc->y.x_dist = 0;
	calc->y.y_dist = 0;
	calc->distance = 0;
}

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

void			init_calcx(t_calc_1 *x, t_vector_2d *dir, t_vector_2d *player, double ray)
{
	x->y_dist += (dir > 0) ? CELL - player->x : player->x;
	x->x_dist += x->y_dist / tan(ray * M_PI / 180);
	x->inmap.y += dir->y;
	x->inmap.x += dir->x * (int)(x->x_dist / CELL);
	x->distance = sqrt(pow(x->y_dist, 2) + pow(x->x_dist, 2));
}

void			init_calcy(t_calc_1 *y, t_vector_2d *dir, t_vector_2d *player, double ray)
{
	y->x_dist += (dir > 0) ? CELL - player->y : player->y;
	y->y_dist += y->x_dist * tan(ray * M_PI / 180);
	y->inmap.x += dir->x;
	y->inmap.y += dir->y * (int)(y->y_dist / CELL);
	y->distance = sqrt(pow(y->y_dist, 2) + pow(y->x_dist, 2));
}

void			first_inter(t_w3dcalc *calc, char **map, double ray, t_vector_2d player)
{
	get_direction(&(calc->direction), ray);
	init_calcx(&(calc->x), &(calc->direction), &player, ray);
	init_calcy(&(calc->y), &(calc->direction), &player, ray);

}

void			launch_ray(t_wall *wall, t_w3dmap *map, double ray, int i)
{
	t_w3dcalc	calc;
	t_vector_2d	first;

	init_w3d_calc(&calc, map->pos);
	ray = get_angle(ray);
	while ((calc.x.inmap.x && calc.x.inmap.y && calc.x.inmap.x < map->size.x && calc.x.inmap.y < map->size.y && map->map[calc.x.inmap.x][calc.x.inmap.y] != '1') && calc.y.inmap.x && calc.y.inmap.y && calc.y.inmap.x < map->size.x && calc.y.inmap.y < map->size.y && map->map[calc.y.inmap.x][calc.y.inmap.y] != '1')
	{
		if ((calc.x.inmap.x == map->pos.x && calc.x.inmap.y == map->pos.y) && (calc.y.inmap.x == map->pos.x && calc.y.inmap.y == map->pos.y))
		{
			first_inter(&calc, map->map, ray, map->cam.player);
			first.x = (int)(calc->x.distance);
			first.y = (int)(calc->y.distance);
		}
	}
	wall->collumns[i] = ;
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
