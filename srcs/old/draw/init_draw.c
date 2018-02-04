/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_draw.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adleau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/19 12:36:30 by adleau            #+#    #+#             */
/*   Updated: 2018/01/19 15:06:25 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <SDL.h>
#include <engine/engine.h>
#include <stdio.h>
#include <sdl/sdl_wrapper.h>

/* this file contains the functions required to initialize the values
** for the visual representation of the main menu
 */

void		init_menu_w3d(t_rect *w3d)
{
	w3d->start.x = WIN_WD / 32;
	w3d->start.y = WIN_HT / 3;
	w3d->end.x = w3d->start.x + WIN_WD / 3 - w3d->start.x;
	w3d->end.y = w3d->start.y * 2;
}

void		init_menu_doom(t_rect *doom)
{
	doom->start.x = WIN_WD / 32 + WIN_WD / 3 ;
	doom->start.y = WIN_HT / 3;
	doom->end.x = doom->start.x + WIN_WD / 3 - WIN_WD / 32;
	doom->end.y = doom->start.y * 2;
}

void		init_menu_duke(t_rect *duke)
{
	duke->start.x = WIN_WD / 32 + 2 * WIN_WD / 3;// - WIN_WD / 32;
	duke->start.y = WIN_HT / 3;
	duke->end.x = duke->start.x + WIN_WD / 3 - WIN_WD / 16;
	duke->end.y = WIN_HT / 3 * 2;
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
