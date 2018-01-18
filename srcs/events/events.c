/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adleau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/16 13:09:57 by adleau            #+#    #+#             */
/*   Updated: 2018/01/18 13:37:42 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <SDL.h>
#include <engine/engine.h>
#include <draw/draw.h>
#define EVENT_PTR eng->mainwindow.event
#define WIN_PTR eng->mainwindow.screen

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
	{
		SDL_DestroyWindow(WIN_PTR);
		exit(1);
	}
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
	while (1)
	{
		while (SDL_PollEvent(&(EVENT_PTR)))
		{
			draw(eng);
			if (EVENT_PTR.type == SDL_QUIT)
			{
				SDL_DestroyWindow(WIN_PTR);
				exit(1);
			}
			else if (EVENT_PTR.type == SDL_KEYUP)
				keyup_events(eng);
			else if (EVENT_PTR.type == SDL_KEYDOWN)
				keydown_events(eng);
			else if (EVENT_PTR.type == SDL_MOUSEMOTION)
				mouse_motion(eng);
		}
	}
}
