/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adleau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/16 14:31:00 by adleau            #+#    #+#             */
/*   Updated: 2018/01/18 16:06:05 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <SDL.h>
#include <engine/engine.h>
#include <stdio.h>
#include <sdl/sdl_wrapper.h>

void		init_menu_w3d(t_rect *w3d)
{
	w3d->start.x = WIN_WD / 16;
	w3d->start.y = WIN_HT / 3;
	w3d->end.x = WIN_WD - w3d->start.x;
	w3d->end.y = w3d->start.y * 2;
}

void		init_menu_doom(t_rect *doom)
{
	doom->start.x = WIN_WD / 16;
	doom->start.y = WIN_HT / 9;
	doom->end.x = WIN_WD - doom->start.x;
	doom->end.y = doom->start.y * 2;
}

void		init_menu_duke(t_rect *duke)
{
	duke->start.x = WIN_WD - WIN_WD / 16;
	duke->start.y = WIN_HT / 9;
	duke->end.x = duke->start.x + WIN_WD / 4;
	duke->end.y = duke->start.y * 2;
}

void		init_menu_title(t_rect *title)
{
	title->start.x = WIN_WD / 16;
	title->start.y = WIN_HT / 9;
	title->end.x = WIN_WD - title->start.x;
	title->end.y = title->start.y * 2;
}

void		init_menu_rectangles(t_menu *menu)
{
	init_menu_title(&(menu->title));
	init_menu_w3d(&(menu->w3d));
	init_menu_doom(&(menu->doom));
	init_menu_duke(&(menu->duke));
}

/* draw_menu function
** draws the main menu allowing to chosse between the different engines
 */

void		draw_menu(const t_engine *eng)
{
	init_menu_rectangles(&(eng->mainwindow.data));
	draw_menu_sub(&(eng->mainwindow.data));
}

/* draw function
** calls everything needed to draw in the window
 */

void		draw(const t_engine *eng)
{
	if (!(eng->picker))
		draw_menu(eng);
}
