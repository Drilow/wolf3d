/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adleau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 08:36:41 by adleau            #+#    #+#             */
/*   Updated: 2018/03/04 17:51:39 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <SDL.h>
#include <mandatory_part/wolf.h>
#include <mandatory_part/walls.h>

void			draw_floor_ceiling(SDL_Surface *surf)
{
	int			x;
	int			y;

	y = -1;
	while (++y <= WIN_HT)
	{
		x = -1;
		while (++x <= WIN_WD)
		{
			if (y <= WIN_HT / 2)
				draw_px(surf, x, y, 0x0000FF);
			else
				draw_px(surf, x, y, 0x00FF00);
		}
	}
}

void			draw_px(SDL_Surface *surf, int x, int y, int color)
{
	t_color		cols;
	Uint32		col;
	Uint32		*pxmem;

	cols.r = color >> 16;
	cols.g = color >> 8;
	cols.b = color;
	col = SDL_MapRGB(surf->format, cols.r, cols.g, cols.b);
	pxmem = (Uint32*)surf->pixels + (y * surf->pitch / surf->format->BytesPerPixel) + x;
	*pxmem = col;
}

Uint32			get_color_from_tex(t_wolf *wolf, int x, int __attribute__((unused))y, t_walls *walls)
{
	t_vector_2d	ratio;
	Uint32		color;
	Uint32		*pxmem;

	if (walls->wall->end - walls->wall->start == 0)
		exit(1);
	color = 0;
	if (walls->collumns[x] <= 0)
		return (0);
//	printf("a %d\n", walls->wall->l_off);
	ratio.x = walls->wall->end - (x + walls->wall->first_proc);
	ratio.y = walls->collumns[x];
	pxmem = (Uint32*)wolf->map.textures + (Uint32)(((walls->wall->index.y * CELL * (wolf->map.textures->pitch / wolf->map.textures->format->BytesPerPixel)) + walls->wall->index.x * CELL * wolf->map.textures->format->BytesPerPixel));
	pxmem += (Uint32)(((((double)x - walls->wall->start) * ((double)walls->wall->end - walls->wall->start)) / CELL) * wolf->wrap->wolf->format->BytesPerPixel);
//	printf("walls->collumns[%d] : %d, y %d\n", x, walls->collumns[x], y);
	pxmem += (Uint32)((((double)y / walls->collumns[x]) * CELL) * (wolf->map.textures->pitch / wolf->map.textures->format->BytesPerPixel));
//	pxmem += (Uint32)(((walls->wall->l_off / WIN_HT) * (wolf->map.textures->pitch / wolf->map.textures->format->BytesPerPixel)));
//	pxmem += (Uint32)(walls->wall->first_proc * wolf->map.textures->format->BytesPerPixel);
	color = *pxmem;
	return (color);
}

void			draw_collumn_tmp(t_wolf *wolf, t_walls *walls, int x)
{
	int			y;
	int			y_onscreen;

	y = -1;
	walls->wall->l_off = 0;
	y_onscreen = WIN_HT / 2 - walls->collumns[x] / 2;
	while (++y + y_onscreen <= WIN_HT && y <= walls->collumns[x])
	{
		if (y + y_onscreen >= 0)
			draw_px(wolf->wrap->wolf, x, y + y_onscreen, get_color_from_tex(wolf, x, y, walls));
		else
			walls->wall->l_off = y;
	}
}
/*
void			draw_collumn(SDL_Surface *surf, SDL_Surface __attribute__((unused))*src, int x, int *collumns, t_wall __attribute__((unused))*wall)
{
	int			y;
	int			y_onscreen;

	y = -1;
	y_onscreen = WIN_HT / 2 - collumns[x] / 2;
	if (collumns[x] >= WIN_HT)
		y_onscreen = 0;
	while (++y + y_onscreen < -1);
	while (++y + y_onscreen <= WIN_HT && y <= collumns[x])
	{
		if (x > 0 && collumns[x] <= 0)
			collumns[x] = collumns[x - 1];
		else if (x == 0 && collumns[x] <= 0 && collumns[x + 1] && collumns[x + 1] > 0)
		{
			collumns[x] = collumns[x + 1];
		}
		draw_px(surf, x, y + y_onscreen, get_color_from_tex(src, wall, x, y, collumns[x]));
	}
}
*/
void			draw_wall_tmp(t_wolf *wolf, t_walls *walls)
{
	int			x;

	x = walls->wall->start - 1;
	while (++x < walls->wall->end && x < WIN_WD)
	{
		draw_collumn_tmp(wolf, walls, x);
	}
}
/*
void			draw_wall(SDL_Surface *surf, SDL_Surface *src, int *collumns, t_wall *wall)
{
	int			x;

	x = wall->start - 1;
	while (++x <= wall->end)
	{
//		printf("dollumn %d || %d %d\n", collumns[x], wall->start, wall->end);
//		if (wall->start == -1 && wall->end == 1280)
//			exit(1);
		draw_collumn(surf, src, x, collumns, wall);
//		printf("collumn %d || %d %d\n", collumns[x], wall->start, wall->end);
	}
	}*/
