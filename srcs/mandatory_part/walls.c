/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabessir <mabessir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 08:36:41 by adleau            #+#    #+#             */
/*   Updated: 2018/03/20 18:06:05 by mabessir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <SDL.h>
#include <mandatory_part/wolf.h>
#include <mandatory_part/walls.h>

void			draw_floor_ceiling(SDL_Surface *surf, SDL_Surface *src,
t_vector_2d *index)
{
	int			x;
	int			y;
	double		ratiox;
	double		ratioy;
	Uint32		color;

	y = -1;
	ratiox = (double)(CELL - 1) / WIN_WD;
	ratioy = (double)(CELL - 1) / WIN_HT;
	while (++y < WIN_HT)
	{
		x = -1;
		while (++x < WIN_WD)
		{
			color = *((Uint32*)src->pixels + (Uint32)((((index->y *
			CELL + (Uint32)(y * ratioy)) *
			(src->pitch / src->format->BytesPerPixel))
			+ (index->x * CELL + (Uint32)(x * ratiox)))));
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
	col = SDL_MapRGB(surf->format,
		cols.r, cols.g, cols.b);
	pxmem = (Uint32*)surf->pixels +
	(y * surf->pitch / surf->format->BytesPerPixel)
	+ x;
	*pxmem = col;
}

static	int		check_walls_collumns_x(t_walls *walls, int x)
{
	if (x > 0)
		walls->collumns[x] = walls->collumns[x - 1];
	else
	{
		walls->collumns[x] = 0;
		return (0);
	}
	return (1);
}

Uint32			get_color_from_tex(t_wolf *wolf, int x, int y, t_walls *walls)
{
	Uint32	color;
	Uint32	*pxmem;
	double	ratiox;
	double	ratioy;

	ratiox = (double)(CELL - 1) / (walls->wall->end - walls->wall->start);
	ratioy = (double)(CELL - 1) / (walls->collumns[x]);
	if (walls->wall->end - walls->wall->start == 0)
		exit(1);
	color = 0;
	if (walls->collumns[x] <= 0)
	{
		if (check_walls_collumns_x(walls, x) == 0)
			return (0);
	}
	pxmem = (Uint32*)wolf->map.textures->pixels +
	(Uint32)((((walls->wall->index.y * CELL
	+ (Uint32)(y * ratioy)) * (wolf->map.textures->pitch
	/ wolf->map.textures->format->BytesPerPixel))
	+ (walls->wall->index.x * CELL +
		(Uint32)((x - walls->wall->start) * ratiox))));
	color = *pxmem;
	return (color);
}
