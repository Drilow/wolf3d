/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf_draw.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adleau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 08:28:28 by adleau            #+#    #+#             */
/*   Updated: 2018/02/09 13:11:36 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <SDL.h>
#include <libft.h>
#include <mandatory_part/wolf.h>
#include <mandatory_part/walls.h>
#include <mandatory_part/w3d_calc.h>
#include <helpers/cleanup.h>

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

int				was_wall_hit(t_w3dcalc *calc, char **map, int flag) // 0 = x, 1 = y
{
	if (flag)
	{
		printf("zbobi %d \n", (int)calc->processed.y / CELL);
		if (calc->end.x)
			return (0);
		if (map[(int)(calc->start.y + (calc->direction.y * calc->processed.y / CELL))][(int)(calc->start.x + calc->direction.x * calc->inc)] != '0' && map[(int)(calc->start.y + (calc->direction.y * calc->processed.y / CELL))][(int)(calc->start.x + calc->direction.x * calc->inc)] != 'S')
		{
			printf("TEUB %d %d %c\n", (int)(calc->start.y + (calc->direction.y * calc->processed.y / CELL)), (int)(calc->start.x + calc->direction.x * calc->inc), map[(int)(calc->start.y + (calc->direction.y * calc->processed.y / CELL))][(int)(calc->start.x + calc->direction.x * calc->inc)]);
//			exit(1);
			calc->end.x = calc->inc;
			return (0);
		}
	}
	else
	{
		if (calc->end.y)
			return (0);
		if (map[(int)(calc->start.y + calc->direction.y * calc->inc)][(int)(calc->start.x + (calc->direction.x * calc->processed.x / CELL))] != '0' && map[(int)(calc->start.y + calc->direction.y * calc->inc)][(int)(calc->start.x + (calc->direction.x * calc->processed.x / CELL))] != 'S')
		{
			calc->end.y = calc->inc;
			return (0);
		}

	}
	return (1);
}

int				get_ht(t_w3dcalc *calc, t_wall *wall)
{
	int			ht;

	ht = 0;
	if ((sqrt(pow((calc->proc_for1.x * (calc->player.y / CELL)), 2) + pow(calc->player.y, 2)) + sqrt(pow((CELL * calc->end.y), 2) + pow(calc->processed.x, 2))) <
		(sqrt(pow((calc->proc_for1.y * (calc->player.x / CELL)), 2) + pow(calc->player.x, 2)) + sqrt(pow((CELL * calc->end.x), 2) + pow(calc->processed.y, 2))))
	{
		ht = (WIN_WD / 2 / tan(30 * M_PI / 180)) * CELL / (sqrt(pow((calc->proc_for1.x * (calc->player.x / CELL)), 2) + pow(calc->player.y, 2)) + sqrt(pow((CELL * calc->end.y), 2) + pow(calc->processed.x, 2)));
		wall->inmap.x = (int)(calc->processed.x / CELL + 1) * calc->direction.x;
		wall->inmap.y = calc->end.y * calc->direction.y;
		printf("1ere\n");
		if (calc->direction.x == -1)
			wall->wall_surf = 0;
		else
			wall->wall_surf = 1;
	}
	else
	{
		ht = (WIN_WD / 2 / tan(30 * M_PI / 180)) * CELL / (sqrt(pow((calc->proc_for1.y * (calc->player.y / CELL)), 2) + pow(calc->player.x, 2)) + sqrt(pow((CELL * calc->inc), 2) + pow(calc->processed.y, 2)));
		wall->inmap.y = (int)(calc->processed.y / CELL + 1) * calc->direction.y;
		wall->inmap.x = calc->end.x * calc->direction.x;
		printf("2eme %d %d || %d ||| %f\n", wall->inmap.y, wall->inmap.x, ht, calc->processed.y);
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
		if (!(calc.end.x))
			calc.processed.x += calc.proc_for1.x;
		if (!(calc.end.y))
			calc.processed.y += calc.proc_for1.y;
		calc.inc++;
	}
	printf("processed %f %f\n", calc.processed.y, calc.processed.x);
	wall->collumns[i] = get_ht(&calc, wall);
}

int				compare_vector_2d(t_vector_2d v1, t_vector_2d v2)
{
	if (v1.x == v2.x && v1.y == v2.y)
		return (0);
	return (1);
}

int				*realloc_dup(int *tab, int len)
{
	int			*new;

	printf("%d\n", len);
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
		ft_memcpy(new, tab, len);
		ft_memdel((void*)&tab);
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

	i= 1;
	if (!(wall->collumns = (int*)malloc(sizeof(int*))))
		free_wolf(wolf, 1);
	printf("launch rays %f\n", *rays);
	launch_ray(wall, &(wolf->map), *rays, 0);
	start = wolf->map.pos;
	*rays += inc;
	printf("%d %d %d %d\n", start.y, start.x, wall->inmap.y, wall->inmap.x);
	while (!compare_vector_2d(add_vectors(wall->inmap, start), start))
	{
		launch_ray(wall, &(wolf->map), *rays, i);
		printf("wololo %d || %d\n", i, wall->collumns[i]);
		if (!(wall->collumns = realloc_dup(wall->collumns, i + 1)))
			free_wolf(wolf, 1);
		printf("wut\n");
		*rays += inc;
		i++;
	}
	printf("%d %d %d %d\n", start.y, start.x, wall->inmap.y, wall->inmap.x);
	printf("zobi\n");
//	exit(1);
	return (i - 1);
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
	printf("camera %f\n", wolf->map.cam.range[0]);
	rays = wolf->map.cam.range[0];
	inc = rays / WIN_WD;
	init_wall(&wall);
	while (++x < WIN_WD && rays <= wolf->map.cam.range[1])
	{
		if (!wall.collumns)
		{
			wall.current = x;
			x += launch_rays(&wall, wolf, &rays, inc);
		}
		draw_wall(wolf->wrap->wolf, pick_wall(wall.wall_surf, wolf->map.walls), wall.current, &wall);
		init_wall(&wall);
	}
	SDL_RenderClear(wolf->wrap->renderer);
	SDL_RenderCopy(wolf->wrap->renderer, wolf->wrap->tex, NULL, NULL);
	SDL_RenderPresent(wolf->wrap->renderer);
}
