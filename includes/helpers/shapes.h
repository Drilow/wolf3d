/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabessir <mabessir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 12:18:17 by mabessir          #+#    #+#             */
/*   Updated: 2018/03/14 12:18:41 by mabessir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHAPES_H
# define SHAPES_H
# include <SDL.h>

typedef struct		s_color
{
	int				r;
	int				g;
	int				b;
}					t_color;

typedef struct		s_vector_2d_d
{
	double			x;
	double			y;
}					t_vector_2d_d;

/*
** s_vector_2d struct
** contains the x and y position of a given point
*/

typedef struct		s_vector_2d
{
	int				x;
	int				y;
}					t_vector_2d;

/*
** s_rect struct
** holds start and ending position of a rectangle in order to draw it on the
** screen
*/

typedef struct		s_rect
{
	t_vector_2d		start;
	t_vector_2d		end;
}					t_rect;

void				draw_rect(t_rect *rect, SDL_Surface *surf, int color);

#endif
