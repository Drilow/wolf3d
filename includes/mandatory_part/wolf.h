/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adleau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 08:26:31 by adleau            #+#    #+#             */
/*   Updated: 2018/02/27 17:52:31 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF_H
# define WOLF_H
# include <helpers/sdl_wrapper.h>
# include <mandatory_part/w3d_parse.h>
# include <mandatory_part/w3d_map.h>
# include <mandatory_part/w3d_calc.h>
# define CELL 64

typedef struct		s_wolf
{
	t_w3dparse		parse;
	t_w3dmap		map;
	t_sdl_wrapper	*wrap;
//	t_w3dcalc		calc;
}					t_wolf;

void				wolf_loop(t_wolf *wolf);
void				w3d_draw(t_wolf *wolf);
void				init_wolf(t_wolf *wolf, t_sdl_wrapper *wrap, char *path);
void				w3d_parse(t_wolf *wolf);

#endif
