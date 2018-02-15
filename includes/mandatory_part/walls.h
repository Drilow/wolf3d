/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adleau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 08:37:54 by adleau            #+#    #+#             */
/*   Updated: 2018/02/15 11:36:37 by adleau           ###   ########.fr       */
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
	int				start; // 0 for first wall, whatever next
	int				end; // tab index
	int				l_off; // left offset : (processed.first * xmaxwall) / processed.size
	int				first_proc; // index of the cell hit < CELL
	int				processed_size; // size from first_proc to end of the wall (CELL - first_proc)
	int				col; // used to export the ht of the collumn
	t_vector_2d		direction; // used to pick the wall
	t_vector_2d		inmap;
	struct s_wall	*next;
}					t_wall;

typedef struct		s_walls
{
	int				*collumns; // all the collumns displayed
	t_wall			*wall;
}					t_walls;

void			draw_wall(SDL_Surface *surf, SDL_Surface *src, int *collumns, t_wall *wall);

#endif
