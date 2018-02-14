/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   w3d_rays.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adleau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/13 17:43:27 by adleau            #+#    #+#             */
/*   Updated: 2018/02/13 17:52:57 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef W3D_RAYS_H
# define W3D_RAYS_H

#include <helpers/shapes.h>

typedef struct			s_w3dray
{
	double				orientation;
	double				angle;
	t_vector_2d			direction;
	t_vector_2d			inmap;
	t_vector_2d			off; // offset for the player in the cell
	t_vector_2d			proc_x; // .x processed .y incremental * CELL
	t_vector_2d			proc_y;
	t_vector_2d			hit; // 1 if proc detected a wall
	t_vector_2d			distance;

}						t_w3dray;

#endif
