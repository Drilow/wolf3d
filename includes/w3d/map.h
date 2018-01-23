/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adleau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/11 19:03:14 by adleau            #+#    #+#             */
/*   Updated: 2018/01/21 21:09:27 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef W3DMAP_H
# define W3DMAP_H
# include <sdl/sdl_wrapper.h>
# include <w3d/camera.h>

/* w3dmap
** holds informations specific to w3d map
 */

typedef struct		s_w3dmap
{
	char			**map_tab;
	t_2dvector		size;
	t_2dvector		pos;
	t_camera		camera;
	char			**walls;
	SDL_Surface		**wall_surf;
}					t_w3dmap;

#endif
