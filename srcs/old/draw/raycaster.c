/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adleau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/21 21:05:43 by adleau            #+#    #+#             */
/*   Updated: 2018/02/01 16:55:11 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <SDL.h>
#include <sdl/sdl_wrapper.h>
#include <engine/engine.h>
#include <draw/raycaster.h>
#include <math.h>
#include <draw/calc.h>
#include <cleanup/cleanup.h>

/* init_rays function
** sets the pointers of the rays structure to NULL
 */

void			init_rays(t_rays *rays)
{
	rays->first = NULL;
	rays->current = NULL;
	rays->last = NULL;
}

/* init_direction function
** initializes the direction vectors according to the camera orientation
 */

void			init_direction(t_2dvector *direction, double orientation)
{
	if (orientation >= 0 && orientation < 180)
		direction->x = 1;
	else
		direction->x = -1;
	if (orientation >= 90 && orientation < 270)
		direction->y = 1;
	else
		direction->y = -1;
}

/* current_ray function
** returns the current projected ray (Field of View / Windows width) * x coord
 */

double			current_ray(t_camera *cam, int x)
{
	return (cam->range_start + (cam->fov / WIN_WD) * x);
}

/* recalc_ang function
** recalculates the angle between the current ray and the horizontal line
** this value will be used to either increment or decrement the index of
** the map while doing the wall research (going up -x, going down +x,
** going left -y, going right +y, 0 and 360 is up, 90 is right, 180 is down
** and 270 is left)
 */

double			recalc_ang(double curr_ray)
{
	if (curr_ray >= 0 && curr_ray < 90)
		return (90 - curr_ray);
	else if (curr_ray >= 90 && curr_ray < 180)
		return (curr_ray - 90);
	else if (curr_ray >= 180 && curr_ray < 270)
		return (270 - curr_ray);
	return (curr_ray - 270);
}

void			init_first_det_and_inc(t_calc *calc, t_w3dmap *map)
{
	calc->firstdet.x = -1;
	calc->firstdet.x = -1;
	calc->firstinc.x = (calc->direction.x == -1) ?
	map->camera.player.x : CELL - map->camera.player.x;
	calc->firstinc.y = (calc->direction.y == -1) ?
	map->camera.player.y : CELL - map->camera.player.y;
}

/* init_calc function
** initializes the members of t_calc structure used by get_collumnsize
 */

void			init_calc(t_calc *calc, t_w3dmap *map)
{
	calc->limits.x = map->size.x;
	calc->limits.y = map->size.y;
	calc->playerpos.x = map->camera.player.x;
	calc->playerpos.y = map->camera.player.y;
	calc->posinmap.x = map->pos.x;
	calc->posinmap.y = map->pos.y;
	calc->detect.x = -1;
	calc->detect.y = -1;
	calc->increment.x = -1;
	calc->increment.y = -1;
	calc->scaled.x = -1;
	calc->scaled.y = -1;
	init_first_det_and_inc(calc, map);
}

void			get_first_inter(t_calc *calc, double ray)
{
	calc->firstdet.x = calc->firstinc.y / tan(ray * M_PI / 180);
//	printf("first det.x %f || %f, %f\n", calc->firstdet.x, calc->firstinc.y, tan(ray)* 0.0174532925);
	calc->firstdet.y = calc->firstinc.x * tan(ray * M_PI / 180);
	calc->firstpos.x = (calc->firstdet.x < calc->firstdet.y) ? calc->firstinc.x : calc->firstdet.x;
	calc->firstpos.x += calc->playerpos.x;
	calc->firstpos.y = (calc->firstdet.y > calc->firstdet.x) ? calc->firstinc.y : calc->firstdet.y;
	calc->firstpos.y += calc->playerpos.y;
}

void			loop_x(char **__attribute__((unused))map_tab, t_calc *__attribute__((unused))calc)
{
}

int				roundup(double d)
{
	if (d - (int)d >= .5)
		return (d - (int)d + 1);
	return ((int)d);
}

/* get_collumnsize function
** projects a ray and returns the size of the collumn hit
 */

int				get_collumnsize(t_w3dmap *map, double curr_ray, t_2dvector *inmap)
{
	t_calc		calc;
	int			size;

	size = -1;
	init_direction(&(calc.direction), current_ray(&(map->camera), curr_ray));
//	printf("%d %d %f\n", calc.direction.x, calc.direction.y, current_ray(&(map->camera), curr_ray));
	curr_ray = recalc_ang(current_ray(&(map->camera), curr_ray));
	init_calc(&calc, map);
//	printf("idk curr %f\n", curr_ray);
	get_first_inter(&calc, curr_ray);
//	printf("idk %d %d || %d %d\n", calc.posinmap.x, calc.posinmap.y, calc.posinmap.y + roundup((calc.firstpos.y / CELL)) * calc.direction.y, calc.posinmap.x + roundup((calc.firstpos.x / CELL))* calc.direction.x);
//	printf("%d\n", abs((int)((map->camera.dist_screen * CELL) / (sqrt(pow(calc.firstpos.x, 2) + pow(calc.firstpos.y, 2))) * (WIN_HT / CELL * 3 / 4))));
	if (calc.posinmap.y + (int)(calc.firstpos.y / CELL * calc.direction.y) >= 0 && calc.posinmap.y + (int)(calc.firstpos.y / CELL * calc.direction.y) < map->size.y && calc.posinmap.x + (int)(calc.firstpos.x / CELL * calc.direction.x) >= 0 && calc.posinmap.x + (int)(calc.firstpos.x / CELL * calc.direction.x) < map->size.x)
	{
		inmap->x = calc.posinmap.x + (int)(calc.firstpos.x / CELL * calc.direction.x);
		inmap->y = calc.posinmap.y + (int)(calc.firstpos.y / CELL * calc.direction.y);
//		if (inmap->y <= 2)
//			printf("add %d %d %c %f\n", inmap->y, inmap->x, map->map_tab[inmap->y][inmap->x], curr_ray);
		if (map->map_tab[inmap->y][inmap->x] == '1')
		{
			return ((int)(map->camera.dist_screen * CELL) / (sqrt(pow(calc.firstpos.x, 2) + pow(calc.firstpos.y, 2))) * cos((90 - curr_ray) *  M_PI / 180));
		}
	}
	printf("wtf inc : %f %f|| det : %f %F || pos : %f %f  || %d\n", calc.firstinc.y, calc.firstinc.x, calc.firstdet.y, calc.firstdet.x, calc.firstpos.y, calc.firstpos.x, (int)(calc.firstpos.x / CELL) * calc.direction.x);
	return (0);
	inmap->x = calc.posinmap.x + (int)(calc.firstpos.x / CELL * calc.direction.x);
	inmap->y = calc.posinmap.y + (int)(calc.firstpos.y / CELL * calc.direction.y);
//	printf("add %d %d || %d %d %f\n", roundup((calc.firstpos.y / CELL)) * calc.direction.y, roundup((calc.firstpos.x / CELL)) * calc.direction.x, inmap->y, inmap->x, curr_ray);
//	printf("dd %d %d\n", inmap->x, inmap->y);
//	loop_x(map->map_tab, &calc);
//	loop_y(tab->map_tab, &calc);
	return (abs((int)((map->camera.dist_screen * CELL) / (sqrt(pow(calc.firstpos.x, 2) + pow(calc.firstpos.y, 2))) * (WIN_HT / CELL))));
}

/* fill_rays function
** fills the rays with informations for display
 */

void			fill_rays(t_engine *eng, t_w3dmap *map, t_rays *rays, int x)
{
	if (!rays->first)
	{
		//printf("bite %d\n", x);
		if (!(rays->first = (t_wall*)malloc(sizeof(t_wall))))
			free_everything(eng, 1);
		rays->first->inmap.x = -1;
		rays->first->inmap.y = -1;
		rays->first->dimensions.x = x;
		rays->first->dimensions.y = get_collumnsize(map, x, &(rays->first->inmap));
	}
	else
	{
		if (!rays->current)
		{
			if (!(rays->current = (t_wall*)malloc(sizeof(t_wall))))
				free_everything(eng, 1);
			rays->first->next = rays->current;
		}
		rays->current->inmap.x = -1;
		rays->current->inmap.y = -1;
		rays->current->dimensions.x = x;
		rays->current->dimensions.y = get_collumnsize(map, x, &(rays->current->inmap));
		rays->current->next = NULL;
		if (x == WIN_WD - 1 || rays->current->inmap.x != rays->first->inmap.x || rays->current->inmap.y != rays->first->inmap.y)
		{
//			printf("chibron %d\n", x);
			rays->last = rays->current;
/*			rays->current = rays->first;
			while (rays->current->next != rays->last)
				rays->current = rays->current->next;
			rays->last = rays->current;
			free(rays->last->next);
			rays->last->next = NULL;
*/			rays->current = rays->first;
		}
		else
		{
			if (!(rays->current->next = (t_wall*)malloc(sizeof(t_wall))))
				free_everything(eng, 1);
			rays->current = rays->current->next;
		}
	}
}

void			draw_wall(t_engine *__attribute__((unused))eng, t_w3dmap *__attribute__((unused))map, t_rays *__attribute__((unused))rays, int __attribute__((unused))x)
{
	t_wall		*tmp;
	t_rect		len;

	len.start.x = rays->first->dimensions.x;
	len.start.y = 0;
	len.end.x = rays->last->dimensions.x;
	printf("map : %d %d\n", rays->first->inmap.y, rays->first->inmap.x);
//	printf("first ray of wall %d %d\n", rays->current->inmap.y, rays->current->inmap.x);
	while (rays->current->next)
	{
//		printf("rays %d\n", rays->current->dimensions.y);
//		printf("%d %d\n", rays->current->inmap.y, rays->current->inmap.x);
//		//printf("pouet %d\n", rays->current->dimensions.x);
		len.end.y = rays->current->dimensions.y;
		draw_collumn(eng->mainwindow.wolf, rays->current->dimensions.x, &len, map->wall_surf[3]);
		tmp = rays->current;
		rays->current = rays->current->next;
		free(tmp);
		tmp = NULL;
	}
	rays->first = NULL;
	rays->current = NULL;
	rays->last = NULL;
}

/* render_w3d function
** loops through the x's and calls the functions to set up and draw a given wall
 */

void			render_w3d(t_engine *eng, t_w3dmap *map, t_rays *rays)
{
	int			x;
	int			i;

	i = 0;
	x = -1;
	while (++x < WIN_WD)
	{
		if (rays->last != NULL)
		{
			//printf("x %d\n", x);
			printf("angle : %f wall drawn %d %d || map %d %d\n", recalc_ang(current_ray(&(map->camera), x)), rays->first->dimensions.x, x, rays->first->inmap.y, rays->first->inmap.x);
			draw_wall(eng, map, rays, x);
			i++;
			x -= 2;
			rays->last = NULL;
		}
		else
		{
			fill_rays(eng, map, rays, x);
//			printf("after fill %d\n", x);
		}
	}
	printf("wall drawn %d %d || map %d %d\n", rays->first->dimensions.x, x, rays->current->inmap.y, rays->current->inmap.x);
	draw_wall(eng, map, rays, x);
}

/* raycaster function
** entry point for the raycasting engine
 */

void			raycaster(t_engine __attribute__((unused))*eng)
{
	t_rays		rays;

	init_rays(&rays);
	render_w3d(eng, &(eng->parser.map), &rays);
}
