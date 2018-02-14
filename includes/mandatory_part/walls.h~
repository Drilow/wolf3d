/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adleau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 08:37:54 by adleau            #+#    #+#             */
/*   Updated: 2018/02/08 13:25:56 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WALLS_H
# define WALLS_H
# include <helpers/shapes.h>

typedef struct		s_range
{
	int				start;
	int				end;
}					t_range;

typedef struct		s_wall
{
	t_range			left; // 0 -> start of wall
	t_range			right; // end of shown wall -> end of wall
	int				*collumns; // array of all the collumns of the wall
	t_vector_2d		direction;
	t_vector_2d		inmap;
	int				wall_surf;
	int				current; // for drawing purposes
}					t_wall;

void			draw_wall(SDL_Surface *surf, SDL_Surface *src, int x_screen, t_wall *wall);

#endif
