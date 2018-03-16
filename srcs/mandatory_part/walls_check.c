/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabessir <mabessir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 15:17:37 by mabessir          #+#    #+#             */
/*   Updated: 2018/03/16 15:20:30 by mabessir         ###   ########.fr       */
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

void		check_wall_b(t_wolf *wolf, int *tmpx, int *tmpy)
{
	if (wolf->map.map[wolf->map.pos.y][wolf->map.pos.x -
	(wolf->map.cam.direction.x)] == '1')
	{
		wolf->map.cam.player.x = *tmpx;
		wolf->map.cam.player.y = *tmpy;
		return ;
	}
	else
	{
		wolf->map.pos.x -= wolf->map.cam.direction.x;
		wolf->map.cam.player.x =
		(wolf->map.cam.direction.x < 0) ? 0 : CELL;
	}
}

void		check_wall_b2(t_wolf *wolf, int *tmpx, int *tmpy)
{
	if (wolf->map.map[wolf->map.pos.y -
	wolf->map.cam.direction.y][wolf->map.pos.x] == '1')
	{
		wolf->map.cam.player.x = *tmpx;
		wolf->map.cam.player.y = *tmpy;
		return ;
	}
	else
	{
		wolf->map.pos.y -= wolf->map.cam.direction.y;
		wolf->map.cam.player.y =
		(wolf->map.cam.direction.y < 0) ? 0 : CELL;
	}
}
