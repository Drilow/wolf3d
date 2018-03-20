/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls_draw.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabessir <mabessir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 11:42:20 by mabessir          #+#    #+#             */
/*   Updated: 2018/03/20 18:06:09 by mabessir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <SDL.h>
#include <mandatory_part/wolf.h>
#include <mandatory_part/walls.h>

void			draw_collumn_tmp(t_wolf *wolf, t_walls *walls, int x)
{
	int			y;
	int			y_onscreen;

	y = -1;
	walls->wall->l_off = 0;
	y_onscreen = WIN_HT / 2 - walls->collumns[x] / 2;
	while (++y + y_onscreen < WIN_HT && y < walls->collumns[x])
	{
		if (y + y_onscreen >= 0)
			draw_px(wolf->wrap->wolf, x, y + y_onscreen,
			get_color_from_tex(wolf, x, y, walls));
		else
			walls->wall->l_off = y;
	}
}

void			draw_wall_tmp(t_wolf *wolf, t_walls *walls)
{
	int			x;

	x = walls->wall->start - 1;
	while (++x <= walls->wall->end && x < WIN_WD)
		draw_collumn_tmp(wolf, walls, x);
}
