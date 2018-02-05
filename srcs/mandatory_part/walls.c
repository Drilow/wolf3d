/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adleau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 08:36:41 by adleau            #+#    #+#             */
/*   Updated: 2018/02/05 11:34:32 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <SDL.h>
#include <mandatory_part/wolf.h>
#include <mandatory_part/walls.h>

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

	color = 0;
	ratio.x = src->w / wall->right.end;
	ratio.y = src->h / wall->collumns[wall->current];
	pxmem = (Uint32*)src->pixels + (Uint32)(((wall->collumns[wall->current] - y) *
	ratio.y * (src->pitch / src->format->BytesPerPixel)) + (wall->right.end - x)
	* ratio.x * src->format->BytesPerPixel);
	color = *pxmem;
	return (color);
}

void			draw_collumn(SDL_Surface *surf, SDL_Surface *src, int x_screen, t_wall *wall)
{
	int			y;
	int			y_onscreen;

	y = -1;
	y_onscreen = WIN_HT / 2 - wall->collumns[wall->current] / 2;
	while (++y < wall->collumns[wall->current])
	{
//		printf("%d %d\n", y + y_onscreen, x_screen);
		draw_px(surf, x_screen, y + y_onscreen, get_color_from_tex(src, wall, wall->current, y));
//		printf("c\n");
	}
//	printf("b\n");
}

void			draw_wall(SDL_Surface *surf, SDL_Surface *src, int x_screen, t_wall *wall)
{
	int			off;

	wall->current = -1;
	off = wall->left.end;
	while (++wall->current < wall->right.end)
	{
		if (wall->current >= wall->left.end && wall->current < wall->right.start)
		{
			draw_collumn(surf, src, x_screen + (wall->current - off), wall);
//			printf("oui?\n");
		}
	}

}
