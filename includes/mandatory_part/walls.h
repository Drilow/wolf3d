/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabessir <mabessir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 08:37:54 by adleau            #+#    #+#             */
/*   Updated: 2018/03/22 11:05:21 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WALLS_H
# define WALLS_H
# include <helpers/shapes.h>
# include <mandatory_part/wolf.h>
# include <mandatory_part/w3d_calc.h>
# include <helpers/cleanup.h>
# include <mandatory_part/w3d_rays.h>

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
void				init_wall(t_wall *wall);
int					init_walls(t_walls *walls);
int					pick_wall(t_wall *wall);
void				check_wall(t_wolf *wolf, int *tmpx, int *tmpy);
void				check_wall2(t_wolf *wolf, int *tmpx, int *tmpy);
void				check_wall_b(t_wolf *wolf, int *tmpx, int *tmpy);
void				check_wall_b2(t_wolf *wolf, int *tmpx, int *tmpy);
void				init_ray(t_wolf *wolf, t_w3dray *w_ray, double c_ray);
void				init_draw(t_wolf *wolf, t_walls *walls);
void				draw_loop(t_wolf *wolf, t_walls *walls);
void				free_walls(t_walls *walls);
void				free_wall(t_wall *wall);
t_vector_2d			detect_wall(t_wolf *wolf,
t_wall *wall, double c_ray, int x);
int					handle_90degrees(t_walls *walls, int x,
double *rays, double *inc);
void				last_if(t_wolf *wolf, t_walls *walls);
void				sdl_handle(t_sdl_wrapper *wrap);
t_vector_2d			get_player(t_vector_2d player, t_vector_2d direction);
void				walls_loop(t_wolf *wolf, t_walls *walls);

#endif
