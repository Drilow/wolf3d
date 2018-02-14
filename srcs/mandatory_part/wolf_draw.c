/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf_draw.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adleau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 08:28:28 by adleau            #+#    #+#             */
/*   Updated: 2018/02/14 18:59:46 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <SDL.h>
#include <libft.h>
#include <mandatory_part/wolf.h>
#include <mandatory_part/walls.h>
#include <mandatory_part/w3d_calc.h>
#include <helpers/cleanup.h>
#include <mandatory_part/w3d_rays.h>

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

void				launch_ray(t_w3dray *w_ray)
{
	if (w_ray->proc_x.x == 0 && w_ray->proc_y.y == 0)
	{
		w_ray->proc_x.y = CELL - w_ray->off.y;
		w_ray->proc_x.x = w_ray->proc_x.y / w_ray->tanner;
		w_ray->proc_y.x = CELL - w_ray->off.x;
		w_ray->proc_y.y = w_ray->proc_y.x * w_ray->tanner;
	}
	else
	{
		if (!(w_ray->distance.x))
		{
			w_ray->proc_x.y += CELL;
			w_ray->proc_x.x = w_ray->proc_x.y / w_ray->tanner;
		}
		if (!(w_ray->distance.y))
		{
			w_ray->proc_y.x += CELL;
			w_ray->proc_y.y = w_ray->proc_y.x * w_ray->tanner;
		}
	}
}

#define PROCX_Y w_ray.inmap.y + (w_ray.direction.y * (w_ray.off.y + w_ray.proc_x.y) / CELL)
#define PROCX_X w_ray.inmap.x + (w_ray.direction.x * (w_ray.off.x + w_ray.proc_x.x) / CELL)
#define PROCY_Y w_ray.inmap.y + (w_ray.direction.y * (w_ray.off.y + w_ray.proc_y.y) / CELL)
#define PROCY_X w_ray.inmap.x + (w_ray.direction.x * (w_ray.off.x + w_ray.proc_y.x) / CELL)

t_vector_2d			detect_wall(t_wolf *wolf, t_wall *wall, double c_ray, int x)
{
	t_w3dray		w_ray;

	init_ray(wolf, &w_ray, c_ray);
	if (wall->inmap.x < 0 && wall->inmap.y < 0)
		wall->start = x;
	while (w_ray.distance.x == 0 || w_ray.distance.y == 0)
	{
		printf("procx %d %d| procy %d %d || c_Ray %f\n", PROCX_Y, PROCX_X, PROCY_Y, PROCY_X, c_ray);
		if (PROCX_Y < wolf->map.size.y && PROCX_X < wolf->map.size.x)
			if ((wolf->map.map[PROCX_Y][PROCX_X] != '0') &&
			(wolf->map.map[PROCX_Y][PROCX_X] != 'S'))
				w_ray.distance.x = get_dist(&(w_ray.proc_x));
		if (PROCY_Y < wolf->map.size.y && PROCY_X < wolf->map.size.x)
			if ((wolf->map.map[PROCY_Y][PROCY_X] != '0') &&
			(wolf->map.map[PROCY_Y][PROCY_X] != 'S'))
				w_ray.distance.y = get_dist(&(w_ray.proc_y));
		printf("preteub\n");
		launch_ray(&w_ray);
		printf("teub %d %D\n", w_ray.distance.x, w_ray.distance.y);
	}
//	printf("procx %d %d| procy %d %d\n", PROCX_Y, PROCX_X, PROCY_Y, PROCY_X);
//	printf("x : %d || proc for x %d %d || for y %d %d\n", x, w_ray.proc_x.y, w_ray.proc_x.x, w_ray.proc_y.y, w_ray.proc_y.x);
	w_ray.inmap.x = (w_ray.distance.x < w_ray.distance.y) ? PROCX_X : PROCY_X;

	w_ray.inmap.y = (w_ray.distance.x < w_ray.distance.y) ? PROCX_Y : PROCY_Y;
	if (wall->inmap.x >= 0 && wall->inmap.y >= 0)
	{
		if (compare_vector_2d(w_ray.inmap, wall->inmap))
			wall->end = x;
		else
			wall->col = (w_ray.distance.x < w_ray.distance.y) ? CELL / w_ray.distance.x * wolf->map.cam.screendist : CELL / w_ray.distance.y * wolf->map.cam.screendist;
	}
	printf("dist x y %d %d\n", w_ray.distance.x, w_ray.distance.y);
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
		printf("a\n");
		if (walls.wall->start < 0)
		{
			walls.wall->inmap = detect_wall(wolf, walls.wall, rays, x);
		}
		else if (walls.wall->end >= 0)
		{
			printf("b\n");
			if (!(walls.wall->next = (t_wall*)malloc(sizeof(t_wall))))
				free_wolf(wolf, 1);
			walls.wall = walls.wall->next;
			init_wall(walls.wall);
		}
		if (walls.wall != NULL)
			walls.wall->inmap = detect_wall(wolf, walls.wall, rays, x);
		printf("%d || %d %d || %d\n", x, walls.wall->inmap.y, walls.wall->inmap.x, walls.wall->col);
		rays += inc;
		printf("g\n");
	}
	walls.wall = start;
}

/*

void			init_w3d_calc(t_w3dcalc *calc, t_w3dmap *map, double ray)
{
	get_direction(&(calc->direction), ray);
	printf("ray %f\n", ray);
	calc->inc = 0;
	calc->start.x = map->pos.x;
	calc->start.y = map->pos.y;
	calc->player.x = (calc->direction.x > 0) ? CELL - map->cam.player.x : map->cam.player.x;
	calc->player.y = (calc->direction.y > 0) ? CELL - map->cam.player.y : map->cam.player.y;
	calc->proc_for1.x = 0;
	calc->proc_for1.y = 0;
	calc->processed.x = 0;
	calc->processed.y = 0;
	calc->end.x = 0;
	calc->end.y = 0;
	calc->distance = 0;
}

int				was_wall_hit(t_w3dcalc *calc, char **map, int flag) // 0 = x, 1 = y
{
	if (flag)
	{
		printf("zbobi %d %d\n", (int)calc->processed.y / CELL, calc->end.x);
		if (calc->end.x)
		{
			printf("KESKISPASS %d\n", calc->end.x);
//			exit(1);
			return (0);
		}
			printf("TEUB inc %d | %d %d | %c ", calc->inc, (int)(calc->start.y + (calc->direction.y * calc->processed.y / CELL)), (int)(calc->start.x + calc->direction.x * calc->inc), map[(int)(calc->start.y + (calc->direction.y * calc->processed.y / CELL))][(int)(calc->start.x + calc->direction.x * calc->inc)]);
			if (map[(int)(calc->start.y + (calc->direction.y * calc->processed.y / CELL))][(int)(calc->start.x + calc->direction.x * (calc->inc - 1))] != '0' && map[(int)(calc->start.y + (calc->direction.y * calc->processed.y / CELL))][(int)(calc->start.x + calc->direction.x * calc->inc)] != 'S')
		{
//			exit(1);
			calc->end.x = calc->inc;
			printf("postteub %d %f\n", calc->end.x,calc->processed.y);
			return (0);
		}
			printf("NOPE %d %f\n", calc->end.x,calc->processed.y);
	}
	else
	{
		printf("boob ");
		printf("calc->end.y %d\n", calc->end.y);
		if (calc->end.y)
			return (0);
		if (map[(int)(calc->start.y + calc->direction.y * calc->inc)][(int)(calc->start.x + (calc->direction.x * calc->processed.x / CELL))] != '0' && map[(int)(calc->start.y + calc->direction.y * calc->inc)][(int)(calc->start.x + (calc->direction.x * calc->processed.x / CELL))] != 'S')
		{
			calc->end.y = calc->inc;
			printf("%d\n", calc->end.y);
			return (0);
		}

	}
	return (1);
}

int				get_ht(t_w3dcalc *calc, t_wall *wall)//, int i)
{
	int			ht;

	ht = 0;
	if ((sqrt(pow((calc->proc_for1.x * (calc->player.x / CELL)), 2) + pow(calc->player.y, 2)) + sqrt(pow((CELL * calc->end.y), 2) + pow(calc->processed.x, 2))) <
		(sqrt(pow((calc->proc_for1.y * (calc->player.y / CELL)), 2) + pow(calc->player.x, 2)) + sqrt(pow((CELL * calc->end.x), 2) + pow(calc->processed.y, 2))))
	{
		ht = (WIN_WD / 2 / tan(30 * M_PI / 180)) * CELL / (sqrt(pow((calc->proc_for1.x * (calc->player.x / CELL)), 2) + pow(calc->player.y, 2)) + sqrt(pow((CELL * calc->end.y), 2) + pow(calc->processed.x, 2)));
		wall->inmap.x = (int)(calc->processed.x / CELL) * calc->direction.x;
		wall->inmap.y = (calc->end.y - 1) * calc->direction.y;
		printf("1ere %d %d || %d ||| %f || calcend %d\n", wall->inmap.y, wall->inmap.x, ht, calc->processed.y, calc->end.x);
//		if (!i)
//			wall->left.end =
		if (calc->direction.x == -1)
			wall->wall_surf = 0;
		else
			wall->wall_surf = 1;
	}
	else
	{
		ht = (WIN_WD / 2 / tan(30 * M_PI / 180)) * CELL / (sqrt(pow((calc->proc_for1.y * (calc->player.y / CELL)), 2) + pow(calc->player.x, 2)) + sqrt(pow((CELL * calc->inc), 2) + pow(calc->processed.y, 2)));
		wall->inmap.y = (int)(calc->processed.y / CELL + 1) * calc->direction.y;
		wall->inmap.x = (calc->end.x - 1) * calc->direction.x;
		printf("2eme %d %d || %d ||| %f || calcend %d\n", wall->inmap.y, wall->inmap.x, ht, calc->processed.y, calc->end.x);
		if (calc->direction.x == -1)
			wall->wall_surf = 2;
		else
			wall->wall_surf = 3;
	}
	return (ht);
}

void			launch_ray(t_wall *wall, t_w3dmap *map, double ray, int i)
{
	t_w3dcalc	calc;

	printf("launch ray %f\n", ray);
	init_w3d_calc(&calc, map, ray);
	ray = get_angle(ray);
	if (ray != 90)
		calc.proc_for1.x = CELL * tan(ray * M_PI / 180);
	else
		calc.proc_for1.x = CELL;
	calc.proc_for1.y = CELL / tan(ray * M_PI / 180);
	printf(" QUE %f %f %f\n", ray, calc.proc_for1.y, calc.proc_for1.x);
	while (was_wall_hit(&(calc), map->map, 0) || was_wall_hit(&(calc), map->map, 1))
	{
		if (!(calc.inc))
		{
			calc.processed.x += (calc.proc_for1.x * (calc.player.x / CELL));
			calc.processed.y += (calc.proc_for1.y * (calc.player.y / CELL));
		}
//		else
//		{
			if (!(calc.end.x))
				calc.processed.x += calc.proc_for1.x;
			if (!(calc.end.y))
				calc.processed.y += calc.proc_for1.y;
//		}
		calc.inc++;
	}
	wall->collumns[i] = get_ht(&calc, wall);
	printf("dreelo processed i %d %f || %f %f || %f %f || %d ||| %d %d\n", i, ray, calc.proc_for1.y, calc.proc_for1.x, calc.processed.y, calc.processed.x, wall->collumns[i], wall->inmap.y, wall->inmap.x);
//	exit(1);
}

int				*realloc_dup(int *tab, int len)
{
	int			*new;

	if (!len && tab)
	{
		if (!(new = (int*)malloc(sizeof(int))))
			return  (NULL);
		ft_memdel((void*)&tab);
		return (new);
	}
	if (!(new = (int*)malloc(sizeof(int) * len)))
		return (NULL);
	if (tab)
	{
		ft_memcpy(new, tab, len - 1);
		printf("NOOOOOON\n");
		if (tab)
			ft_memdel((void*)&tab);
		printf("OK\n");
	}
	return (new);
}

t_vector_2d		add_vectors(t_vector_2d v1, t_vector_2d v2)
{
	t_vector_2d	ret;

	ret.x = v1.x + v2.x;
	ret.y = v1.y + v2.y;
	return (ret);
}

int				launch_rays(t_wall *wall, t_wolf *wolf, double *rays, double inc)
{
	int			i;
	t_vector_2d	start;

	i= 0;
	start.x = -1;
	start.y = -1;
//	printf("%d %d %d %d\n", start.y, start.x, wall->inmap.y, wall->inmap.x);
	while ((start.x == -1 && start.y == -1) || (!compare_vector_2d(wall->inmap, start) && *rays <= wolf->map.cam.range[1]))
	{
		if (!(wall->collumns = (int*)realloc(wall->collumns, sizeof(int) * (i + 1))))
			free_wolf(wolf, 1);
		launch_ray(wall, &(wolf->map), *rays, i);
		if (!i)
			start = wall->inmap;
		printf("wololo %d || %d | %f", i, wall->collumns[i], *rays);
		printf("zob %d %d %d %d\n", start.y, start.x, wall->inmap.y, wall->inmap.x);
		*rays += inc;
		i++;
	}
	printf("wut %d\n", wall->collumns[i - 1]);
	printf("zobi %d %f ", i, *rays);
	printf("%d %d %d %d\n", start.y, start.x, wall->inmap.y, wall->inmap.x);
//	exit(1);
	return (i - 1);
}

void		init_wall(t_wall *wall)
{
	wall->left.start = -1;
	wall->left.end = -1;
	wall->right.start = -1;
	wall->right.end = -1;
	if (wall->collumns)
		free(wall->collumns);
	wall->collumns = NULL;
	wall->current = -1;
	wall->direction.x = 0;
	wall->direction.y = 0;
	wall->inmap.x = 0;
	wall->inmap.y = 0;
}

SDL_Surface		*pick_wall(int i, SDL_Surface **walls)
{
	return (walls[i]);
}

void		w3d_draw(t_wolf *wolf)
{
	double	rays;
	double	inc;
	int		x;
	t_wall	wall;

	x = -1;
	printf("camera %f\n", wolf->map.cam.range[0]);
	rays = wolf->map.cam.range[0];
	inc = (wolf->map.cam.range[1] - wolf->map.cam.range[0]) / WIN_WD;
	init_wall(&wall);
	while (++x < WIN_WD && rays <= wolf->map.cam.range[1])
	{
		if (!wall.collumns)
		{
			wall.current = x;
			wall.left.end = 0;
			x += launch_rays(&wall, wolf, &rays, inc);
			wall.right.start = x;
			wall.right.end = x;
			printf("dr dorito %d || %d ||\n", x, wall.collumns[0]);
		}
		draw_wall(wolf->wrap->wolf, pick_wall(wall.wall_surf, wolf->map.walls), wall.current, &wall);
		free(wall.collumns);
		wall.collumns = NULL;
		init_wall(&wall);
	}
	printf("end %d %f\n", x, rays);
	exit(1);
	printf("mais que se passe t il?\n");
	SDL_RenderClear(wolf->wrap->renderer);
	SDL_RenderCopy(wolf->wrap->renderer, wolf->wrap->tex, NULL, NULL);
	SDL_RenderPresent(wolf->wrap->renderer);
}

*/
