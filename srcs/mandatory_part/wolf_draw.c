/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf_draw.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adleau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 08:28:28 by adleau            #+#    #+#             */
/*   Updated: 2018/02/05 11:36:53 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <SDL.h>
#include <mandatory_part/wolf.h>
#include <mandatory_part/walls.h>

void		w3d_draw(t_wolf *wolf)
{
	t_wall	wall;

	wall.left.start = 0;
	wall.left.end = 50;
	wall.right.start = 200;
	wall.right.end = 200;
	if (!(wall.collumns = (int*)malloc(sizeof(int) * 201)))
		exit(1);
	int i;
	int size;
	i = -1;
	size = 25;
	while (++i < 200)
	{
		if (i % 2)
			size++;
		wall.collumns[i] = size;
	}
	printf("qwerty %p\n", wolf->map.walls[1]);
	draw_wall(wolf->wrap->wolf, wolf->map.walls[3], 0, &wall);
	SDL_RenderClear(wolf->wrap->renderer);
	SDL_RenderCopy(wolf->wrap->renderer, wolf->wrap->tex, NULL, NULL);
	SDL_RenderPresent(wolf->wrap->renderer);
//	wolf->wrap->drawn = 1;
}
