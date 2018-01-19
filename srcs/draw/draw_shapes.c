/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_shapes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adleau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/19 13:06:20 by adleau            #+#    #+#             */
/*   Updated: 2018/01/19 14:50:46 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <SDL.h>
#include <sdl/sdl_wrapper.h>

#include <stdio.h>

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



