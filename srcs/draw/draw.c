/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adleau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/16 14:31:00 by adleau            #+#    #+#             */
/*   Updated: 2018/01/23 15:42:35 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cleanup/cleanup.h>
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
	if (!(eng->mainwindow.renderer) && !eng->mainwindow.tex)
	{
		if (!(eng->mainwindow.renderer = SDL_CreateRenderer(eng->mainwindow.screen, -1, SDL_RENDERER_ACCELERATED)))
		{
			printf("%s\n", SDL_GetError());
			free_everything(eng, 1);
		}
		if (!(eng->mainwindow.tex = SDL_CreateTextureFromSurface(eng->mainwindow.renderer, eng->mainwindow.menu)))
		{
			printf("%s\n", SDL_GetError());
			free_everything(eng, 1);
		}
	}
	SDL_RenderClear(eng->mainwindow.renderer);
	SDL_RenderCopy(eng->mainwindow.renderer, eng->mainwindow.tex, NULL, NULL);
	SDL_RenderPresent(eng->mainwindow.renderer);
	eng->to_be_drawn = 1;
}

/* draw function
** calls everything needed to draw in the window
 */

void		draw(t_engine *eng)
{
	if (!(eng->picker))
		draw_menu(eng);
}
