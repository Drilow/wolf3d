/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_shapes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adleau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/19 13:06:20 by adleau            #+#    #+#             */
/*   Updated: 2018/01/23 15:47:57 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <SDL.h>
#include <sdl/sdl_wrapper.h>

#include <stdio.h>

/* get_color_from_tex function
** gets the matching color for the scaled pixel
 */

Uint32			get_color_from_tex(SDL_Surface *source, t_2dvector *atm, t_rect *col)
{
	t_2dvector	ratio;
	Uint32		color;
	Uint32		*pxmem;

	ratio.x = source->w / (col->end.x - col->start.x);
	ratio.y = source->h / (col->end.y - col->start.y);
	pxmem = (Uint32*)source->pixels + (Uint32)(((col->end.y - atm->y) * ratio.y * (source->pitch / source->format->BytesPerPixel)) + (col->end.x - atm->x) * ratio.x * source->format->BytesPerPixel);
	color = *pxmem;
	return (color);
}

/* draw_collumn function
** draws a collumn of wall to a given surface with pixels from the source surface
** len parameter are the dimensions of the scaled wall to print
 */

void			draw_collumn(SDL_Surface *surf, int x, t_rect *len, SDL_Surface *source)
{
	t_rect		col;
	t_2dvector	atm;

	col.end.y = WIN_HT / 2 + len->end.y / 2;
	col.start.y = col.end.y - len->end.y - 1;
	col.start.x = len->start.x;
	col.end.x = len->end.x;
	atm.y = col.start.y;
	atm.x = x;
	while (++atm.y < col.end.y)
		draw_px(surf, x, atm.y, get_color_from_tex(source, &atm, &col));
}

/* draw_px function
** draws a pixel on a given SDL_Surface
 */

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

/* draw_rect
** Requires a rec (start + end position), a SDL surface and a color
 */

void			draw_rect(t_rect *rect, SDL_Surface *surf, int color)
{
	int			x;
	int			y;
	t_color		cols;
	Uint32		col;
	Uint32		*pxmem;

	cols.r = color >> 16;
	cols.g = color >> 8;
	cols.b = color;
	col = SDL_MapRGB(surf->format, cols.r, cols.g, cols.b);
	y = rect->start.y - 1;
	while (++y < rect->end.y)
	{
		x = rect->start.x - 1;
		while (++x < rect->end.x)
		{
			pxmem = (Uint32*)surf->pixels + (y * surf->pitch / surf->format->BytesPerPixel) + x;
			*pxmem = col;
		}
	}
}
