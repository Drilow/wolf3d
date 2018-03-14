/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabessir <mabessir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 08:37:54 by adleau            #+#    #+#             */
/*   Updated: 2018/03/14 12:17:07 by mabessir         ###   ########.fr       */
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
	int				start;
	int				end;
	int				l_off;
	int				first_proc;
	int				processed_size;
	int				col;
	int				flag;
	int				detected;
	t_vector_2d		direction;
	t_vector_2d		inmap;
	t_vector_2d		index;
	double			orientation;
	struct s_wall	*next;
}					t_wall;

typedef struct		s_walls
{
	int				*collumns;
	t_wall			*wall;
}					t_walls;

void				draw_px(SDL_Surface *surf, int x, int y, int color);
void				draw_wall(SDL_Surface *surf, SDL_Surface *src,
int *collumns, t_wall *wall);
void				draw_wall_tmp(t_wolf *wolf, t_walls *walls);
void				draw_floor_ceiling(SDL_Surface *surf,
SDL_Surface *src, t_vector_2d *index);
Uint32				get_color_from_tex(t_wolf *wolf, int x,
int y, t_walls *walls);

#endif
