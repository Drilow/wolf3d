#include <SDL.h>
#include <helpers/shapes.h>

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
