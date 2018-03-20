/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   w3d_rays.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabessir <mabessir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/13 17:43:27 by adleau            #+#    #+#             */
/*   Updated: 2018/03/20 10:06:22 by mabessir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef W3D_RAYS_H
# define W3D_RAYS_H

# include <helpers/shapes.h>

typedef struct			s_w3dray
{
	double				orientation;
	double				angle;
	double				tanner;
	t_vector_2d			dir;
	t_vector_2d			inmap;
	t_vector_2d			off;
	t_vector_2d			proc_x;
	t_vector_2d			proc_y;
	t_vector_2d			hit;
	t_vector_2d			distance;
}						t_w3dray;

void					launch_ray(t_w3dray *w_ray, t_vector_2d *size);

#endif
