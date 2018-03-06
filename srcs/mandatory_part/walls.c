/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adleau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 08:36:41 by adleau            #+#    #+#             */
/*   Updated: 2018/03/06 20:38:44 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <SDL.h>
#include <mandatory_part/wolf.h>
#include <mandatory_part/walls.h>

void			draw_floor_ceiling(SDL_Surface *surf, SDL_Surface *src, t_vector_2d *index)
{
	int			x;
	int			y;
	double		ratiox;
	double		ratioy;
	Uint32		color;

	y = -1;
	ratiox = (double)(CELL - 1) / WIN_WD;
	ratioy = (double)(CELL - 1) / WIN_HT;
	while (++y <= WIN_HT)
	{
		x = -1;
		while (++x <= WIN_WD)
		{
			color = *((Uint32*)src->pixels + (Uint32)((((index->y * CELL + (Uint32)(y * ratioy)) * (src->pitch / src->format->BytesPerPixel)) + (index->x * CELL + (Uint32)(x * ratiox)))));
			draw_px(surf, x, y, color);
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

Uint32			get_color_from_tex(t_wolf *wolf, int x, int y, t_walls *walls)
{
	Uint32		color;
	Uint32		*pxmem;
	double ratiox;
	double ratioy;

	ratiox = (double)(CELL - 1) / (walls->wall->end - walls->wall->start);
	ratioy = (double)(CELL - 1) / (walls->collumns[x]);
	if (walls->wall->end - walls->wall->start == 0)
		exit(1);
	color = 0;
	if (walls->collumns[x] <= 0)
	{
		if (x > 0)
			walls->collumns[x] = walls->collumns[x - 1];
		else
		{
			walls->collumns[x] = 0;
			return (0);
		}
	}
	pxmem = (Uint32*)wolf->map.textures->pixels + (Uint32)((((walls->wall->index.y * CELL + (Uint32)(y * ratioy)) * (wolf->map.textures->pitch / wolf->map.textures->format->BytesPerPixel)) + (walls->wall->index.x * CELL + (Uint32)((x - walls->wall->start) * ratiox))));
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

void			draw_wall_tmp(t_wolf *wolf, t_walls *walls)
{
	int			x;

	x = walls->wall->start - 1;
	while (++x <= walls->wall->end && x < WIN_WD)
		draw_collumn_tmp(wolf, walls, x);
}
