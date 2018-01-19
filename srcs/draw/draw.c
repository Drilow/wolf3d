/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adleau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/16 14:31:00 by adleau            #+#    #+#             */
/*   Updated: 2018/01/19 16:00:05 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <SDL.h>
#include <engine/engine.h>
#include <stdio.h>
#include <sdl/sdl_wrapper.h>

void		draw_menu_sub(t_engine *const eng)
{
	draw_rect(&(eng->mainwindow.data.title), eng->mainwindow.menu, 0xFFFFFF);
	draw_rect(&(eng->mainwindow.data.w3d), eng->mainwindow.menu, 0xFF0000);
	draw_rect(&(eng->mainwindow.data.doom), eng->mainwindow.menu, 0xFF0000);
	draw_rect(&(eng->mainwindow.data.duke), eng->mainwindow.menu, 0xFF0000);
}

/* draw_menu function
** draws the main menu allowing to chosse between the different engines
 */

void		draw_menu(t_engine *const eng)
{
	init_menu_rectangles(&(eng->mainwindow.data));
	draw_menu_sub(eng);
	eng->mainwindow.renderer = SDL_CreateRenderer(eng->mainwindow.screen, -1, SDL_RENDERER_ACCELERATED);
	eng->mainwindow.tex = SDL_CreateTextureFromSurface(eng->mainwindow.renderer, eng->mainwindow.menu);
	SDL_RenderClear(eng->mainwindow.renderer);
	SDL_RenderCopy(eng->mainwindow.renderer, eng->mainwindow.tex, NULL, NULL);
	SDL_RenderPresent(eng->mainwindow.renderer);
}

/* draw function
** calls everything needed to draw in the window
 */

void		draw(t_engine *eng)
{
	if (!(eng->picker))
		draw_menu(eng);
}
