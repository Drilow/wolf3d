/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adleau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/21 21:05:43 by adleau            #+#    #+#             */
/*   Updated: 2018/01/23 15:49:02 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <SDL.h>
#include <engine/engine.h>

/* raycaster function
** entry point for the raycasting engine
 */

void			raycaster(t_engine __attribute__((unused))*eng)
{
	t_rect		len;
	int			x;

	x = 99;
	len.start.x = 100;
	len.end.x = 200;
	len.start.y = 0;
	len.end.y = 100;
	printf("burne %p\n", eng->parser.map.wall_surf[0]);
	while (++x < len.end.x)
	{
		draw_collumn(eng->mainwindow.wolf, x, &len, eng->parser.map.wall_surf[0]);
	}
	printf("pouet\n");
}
