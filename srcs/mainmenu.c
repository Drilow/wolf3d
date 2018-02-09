/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mainmenu.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adleau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 14:11:48 by adleau            #+#    #+#             */
/*   Updated: 2018/02/08 14:11:51 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <menu.h>
#include <engine.h>
#include <helpers/cleanup.h>
#include <helpers/shapes.h>

#include <stdio.h>

void			drawmainmenu(t_engine *eng)
{
	draw_rect(&(eng->mainmenu.w3d), eng->wrap.menu, 0xFF0000);
	draw_rect(&(eng->mainmenu.bonus), eng->wrap.menu, 0x0000FF);
	if (!(eng->wrap.renderer) && !eng->wrap.tex)
	{
		if (!(eng->wrap.renderer = SDL_CreateRenderer(eng->wrap.screen, -1, SDL_RENDERER_ACCELERATED)))
		{
			printf("%s\n", SDL_GetError());
			free_menu(&(eng->mainmenu), &(eng->wrap), 1);
		}
		if (!(eng->wrap.tex = SDL_CreateTextureFromSurface(eng->wrap.renderer, eng->wrap.menu)))
		{
			printf("%s\n", SDL_GetError());
			free_menu(&(eng->mainmenu), &(eng->wrap), 1);
		}
	}
	SDL_RenderClear(eng->wrap.renderer);
	SDL_RenderCopy(eng->wrap.renderer, eng->wrap.tex, NULL, NULL);
	SDL_RenderPresent(eng->wrap.renderer);
	eng->wrap.drawn = 1;
}
