/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adleau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/16 13:09:57 by adleau            #+#    #+#             */
/*   Updated: 2018/01/28 14:48:19 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <cleanup/cleanup.h>
#include <SDL.h>
#include <engine/engine.h>
#include <draw/draw.h>
#define EVENT_PTR eng->mainwindow.event
#define WIN_PTR eng->mainwindow.screen

#include <stdio.h>

/* Select_Game function
** allows you to pick a game from the mouse button input
 */

void			select_game(t_engine *eng, int x, int y)
{
	if ((x >= eng->mainwindow.data.w3d.start.x && x <= eng->mainwindow.data.w3d.end.x) && (y >= eng->mainwindow.data.w3d.start.y && y <= eng->mainwindow.data.w3d.end.y))
	{
		eng->parser.parse_f = parse_w3d;
		eng->parser.path = ft_strdup("maps/wolf3d/lvl1.w3dmap");
		eng->picker = 1;
		eng->to_be_drawn = 0;
		eng->draw = draw_w3d;
	}
}

/* mouseup events
** catches mouseup events and acts accordingly
 */

void			mouseup_events(t_engine __attribute__((unused))*eng)
{
	if (EVENT_PTR.button.button == SDL_BUTTON_LEFT)
	{
		;
	}
}

/* Mouse_motion
** catches mouse motion
 */

void			mouse_motion(t_engine __attribute__((unused))*eng)
{
	;
}

/* Keyup events
** catches events on keyup
 */

void			keyup_events(t_engine *eng)
{
	if (EVENT_PTR.key.keysym.sym == SDLK_ESCAPE)
		free_everything(eng, 0);
}

/* Keydown events
** catches events on keydown
 */

void			keydown_events(t_engine __attribute__((unused))*eng)
{
	;
}

/* engine main loop
** catches events and calls the adequate functions
 */

void			engine_loop(t_engine *eng)
{
	if (!eng->to_be_drawn)
	{
		eng->draw(eng);
	}
	if (!eng->picker)
	{
		SDL_WaitEvent(&(EVENT_PTR));
		if (EVENT_PTR.type == SDL_MOUSEBUTTONUP)
			select_game(eng, EVENT_PTR.button.x, EVENT_PTR.button.y);
		if (EVENT_PTR.type == SDL_KEYUP && EVENT_PTR.key.keysym.sym == SDLK_ESCAPE)
			free_everything(eng, 0);
	}
	while (SDL_PollEvent(&(EVENT_PTR)))
	{
		if (EVENT_PTR.type == SDL_QUIT)
			free_everything(eng, 0);
		else if (EVENT_PTR.type == SDL_KEYUP)
			keyup_events(eng);
		else if (EVENT_PTR.type == SDL_KEYDOWN)
			keydown_events(eng);
		else if (EVENT_PTR.type == SDL_MOUSEMOTION)
			mouse_motion(eng);
		else if (EVENT_PTR.type == SDL_MOUSEBUTTONUP)
			mouseup_events(eng);
	}
}
