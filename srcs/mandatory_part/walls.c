/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adleau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 08:36:41 by adleau            #+#    #+#             */
/*   Updated: 2018/02/21 15:00:31 by adleau           ###   ########.fr       */
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

Uint32			get_color_from_tex(SDL_Surface *src, t_wall *wall, int x, int y)
{
	t_vector_2d	ratio;
	Uint32		color;
	Uint32		*pxmem;

	printf("a\n");
	color = 0;
	ratio.x = src->w / (wall->end - wall->start/* + wall->l_off*/);
	ratio.y = src->h / y;
	pxmem = (Uint32*)src->pixels + (Uint32)(((y * ratio.y * (src->pitch / src->format->BytesPerPixel)) + (wall->end - x /*+ wall->l_off*/) * ratio.x * src->format->BytesPerPixel));
	color = *pxmem;
	printf("col wall->end %d wall->start %d wall->l_off %f || x : %d y : %d\n", wall->end, wall->start, wall->l_off, x, y);
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
		draw_px(surf, x, y + y_onscreen, 0xFFFFFF);//get_color_from_tex(src, wall, x, collumns[x]));
//		printf("maerde %d || %d\n", x_screen,  y + y_onscreen);
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
