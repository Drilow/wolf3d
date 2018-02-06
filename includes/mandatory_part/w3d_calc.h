/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   w3d_calc.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adleau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/06 09:15:17 by adleau            #+#    #+#             */
/*   Updated: 2018/02/06 10:48:57 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef W3D_CALC_H
# define W3D_CALC_H

typedef struct			s_calc_1
{
	double				x_dist;
	double				y_dist;
	double				distance; // ray length
	t_vector_2d			inmap;

}						t_calc_1;

typedef struct			s_w3dcalc
{
	t_calc_1			x; // calculate x, inc y
	t_calc_1			y;
	t_vector_2d			direction;
	double				distance;
}						t_w3dcalc;

#endif
