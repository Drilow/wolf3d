/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adleau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/16 14:31:00 by adleau            #+#    #+#             */
/*   Updated: 2018/01/16 17:50:54 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <SDL.h>
#include <engine/engine.h>

/* draw_menu function
** draws the main menu allowing to chosse between the different engines
 */

void		draw_menu(t_engine *eng)
{
	Uint32 rmask, gmask, bmask, amask;

	/* SDL interprets each pixel as a 32-bit number, so our masks must depend
	   on the endianness (byte order) of the machine */
	#if SDL_BYTEORDER == SDL_BIG_ENDIAN
	rmask = 0xff000000;
	gmask = 0x00ff0000;
	bmask = 0x0000ff00;
	amask = 0x000000ff;
	#else
	rmask = 0x000000ff;
	gmask = 0x0000ff00;
	bmask = 0x00ff0000;
	amask = 0xff000000;
	#endif

	eng->mainwindow->menu = SDL_CreateRGBSurface(0, width, height, 32, rmask, gmask, bmask, amask);
}

/* draw function
** calls everything needed to draw in the window
 */

void		draw(t_engine *eng)
{
	if (!(eng->picker))
		draw_menu(eng);
}
