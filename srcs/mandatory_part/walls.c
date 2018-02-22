/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adleau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 08:36:41 by adleau            #+#    #+#             */
/*   Updated: 2018/02/22 15:47:47 by adleau           ###   ########.fr       */
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

Uint32			get_color_from_tex(SDL_Surface *src, t_wall *wall, int x, int y, int size)
{
	t_vector_2d	ratio;
	Uint32		color;
	Uint32		*pxmem;

	if (wall->end - wall->start == 0)
	{
		printf("col wall->end %d wall->start %d wall->l_off %d wall->first_proc %d|| x : %d y : %d\n", wall->end, wall->start, wall->l_off, wall->first_proc, x, y);
		exit(1);
		return (0);
	}
	color = 0;
	ratio.x = src->w / (wall->end - wall->start);
	ratio.y = src->h / size;
	wall->l_off = src->w - src->w * ((double)wall->first_proc / CELL);
//	printf("%d %d || %d\n", ratio.y, ratio.x, (((size - y) * ratio.y * (src->pitch / src->format->BytesPerPixel)) + ((wall->end - x) * ratio.x * src->format->BytesPerPixel)));
//	exit(1);
//	printf("src->format->BytesPerPixel %d || %d %d || wall start %d end %d\n", src->format->BytesPerPixel, wall->l_off, wall->first_proc, wall->start, wall->end);
	pxmem = (Uint32*)src->pixels + (Uint32)(((size - y) * ratio.y * (src->pitch / src->format->BytesPerPixel)) + ((wall->end - x) * ratio.x * src->format->BytesPerPixel));
//	printf("test\n");
//(((y * ratio.y * (src->pitch / src->format->BytesPerPixel)) + (wall->l_off * (src->pitch * src->format->BytesPerPixel)) + (wall->l_off + wall->end - x) * ratio.x * src->format->BytesPerPixel));
	color = *pxmem;
	return (color);
}

void			draw_collumn(SDL_Surface *surf, SDL_Surface __attribute__((unused))*src, int x, int *collumns, t_wall __attribute__((unused))*wall)
{
	int			y;
	int			y_onscreen;

	y = -1;
	y_onscreen = WIN_HT / 2 - collumns[x] / 2;
	if (collumns[x] >= WIN_HT)
		y_onscreen = 0;
	while (++y <= WIN_HT && y <= collumns[x])
	{
//		printf("%d %d\n", y + y_onscreen, x_screen);
		if (y + y_onscreen >= WIN_HT)
		{
			printf("x %d, y onscreen %d both %d, %f\n", x, y_onscreen, y + y_onscreen, wall->orientation);
		}
		draw_px(surf, x, y + y_onscreen, get_color_from_tex(src, wall, x, y, collumns[x]));
//		printf("maerde\n");
	}
//	printf("b\n");
}

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
}
