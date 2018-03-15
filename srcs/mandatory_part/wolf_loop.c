/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabessir <mabessir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 08:27:33 by adleau            #+#    #+#             */
/*   Updated: 2018/03/15 16:53:15 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mandatory_part/wolf.h>
#include <helpers/cleanup.h>
#include <SDL.h>
#define EVENT_PTR wolf->wrap->event
#define WIN_PTR wolf->wrap->screen

void		check_wall(t_wolf *wolf, int *tmpx, int *tmpy)
{
	if (wolf->map.map[wolf->map.pos.y][wolf->map.pos.x +
	(wolf->map.cam.direction.x)] == '1')
	{
		wolf->map.cam.player.x = *tmpx;
		wolf->map.cam.player.y = *tmpy;
		return ;
	}
	else
	{
		wolf->map.pos.x += wolf->map.cam.direction.x;
		wolf->map.cam.player.x =
		(wolf->map.cam.direction.x > 0) ? 0 : CELL;
	}
}

void		check_wall2(t_wolf *wolf, int *tmpx, int *tmpy)
{
	if (wolf->map.map[wolf->map.pos.y +
	wolf->map.cam.direction.y][wolf->map.pos.x] == '1')
	{
		wolf->map.cam.player.x = *tmpx;
		wolf->map.cam.player.y = *tmpy;
		return ;
	}
	else
	{
		wolf->map.pos.y += wolf->map.cam.direction.y;
		wolf->map.cam.player.y =
		(wolf->map.cam.direction.y > 0) ? 0 : CELL;
	}
}

void		keyup_up(t_wolf *wolf)
{
	int		tmpx;
	int		tmpy;

	tmpx = wolf->map.cam.player.x;
	tmpy = wolf->map.cam.player.y;
	wolf->map.cam.player.x += (wolf->map.cam.direction.x *
	8 * (cos(wolf->map.cam.angle * M_PI / 180)));
	wolf->map.cam.player.y += (wolf->map.cam.direction.y *
	8 * sin(wolf->map.cam.angle * M_PI / 180));
	if (wolf->map.cam.player.x >= CELL - 1 || wolf->map.cam.player.x < 1)
		check_wall(wolf, &tmpx, &tmpy);
	if (wolf->map.cam.player.y >= CELL - 1 || wolf->map.cam.player.y < 1)
		check_wall2(wolf, &tmpx, &tmpy);
}

void		keyup_events_w3d(t_wolf *wolf)
{
	if (EVENT_PTR.key.keysym.sym == SDLK_ESCAPE)
	{
		free_sdl_wrapper(wolf->wrap);
		exit(0);
	}
	else if (EVENT_PTR.key.keysym.sym == SDLK_RIGHT)
	{
		wolf->map.cam.orientation += 5;
		if (wolf->map.cam.orientation >= 360)
			wolf->map.cam.orientation -= 360;
	}
	else if (EVENT_PTR.key.keysym.sym == SDLK_LEFT)
	{
		wolf->map.cam.orientation -= 5;
		if (wolf->map.cam.orientation < 0)
			wolf->map.cam.orientation += 360;
	}
	else if (EVENT_PTR.key.keysym.sym == SDLK_UP)
		keyup_up(wolf);
}

/*
** wolf_loop function
** infinite loop to handle the w3d engine
*/

void		wolf_loop(t_wolf *wolf)
{
	int		istrue;

	istrue = 1;
	while (istrue)
	{
		while (SDL_PollEvent(&(EVENT_PTR)))
		{
			w3d_draw(wolf);
			if (EVENT_PTR.type == SDL_QUIT)
				exit(0);
			else if (EVENT_PTR.type == SDL_KEYDOWN)
				keyup_events_w3d(wolf);
		}
	}
}
