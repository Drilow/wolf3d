/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   w3d.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adleau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/11 14:29:01 by adleau            #+#    #+#             */
/*   Updated: 2018/01/11 19:32:24 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef W3D_H
# define W3D_H

struct s_w3dmap;
struct s_sdl_wrapper;
struct s_calcs;

typedef struct				s_w3d
{
	struct s_w3dmap			map;
	struct s_sdl_wrapper	sdl_wrap;
	struct s_calcs			calcs;
}							t_w3d;

#endif
