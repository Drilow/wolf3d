/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabessir <mabessir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 08:26:31 by adleau            #+#    #+#             */
/*   Updated: 2018/03/20 15:12:12 by mabessir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF_H
# define WOLF_H
# include <helpers/sdl_wrapper.h>
# include <mandatory_part/w3d_parse.h>
# include <mandatory_part/w3d_map.h>
# include <mandatory_part/w3d_calc.h>
# include <mandatory_part/w3d_rays.h>
# define CELL 64

typedef struct		s_wolf
{
	t_w3dparse		parse;
	t_w3dmap		map;
	t_sdl_wrapper	*wrap;
	int				x;
	int				i;
	int				spawn;
}					t_wolf;

void				wolf_loop(t_wolf *wolf);
void				w3d_draw(t_wolf *wolf);
void				init_wolf(t_wolf *wolf, t_sdl_wrapper *wrap, char *path);
void				w3d_parse(t_wolf *wolf);
int					get_map_infos(t_wolf *wolf, t_w3dmap *map, char *line);
void				w3d_draw(t_wolf *wolf);
int					compare_vector_2d(t_vector_2d v1, t_vector_2d v2);
int					get_dist(t_vector_2d *proc);
void				handle_overflow(t_w3dray *w_ray, t_vector_2d size);

#endif
