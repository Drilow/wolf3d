/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   w3d_calc.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adleau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/06 09:15:17 by adleau            #+#    #+#             */
/*   Updated: 2018/02/08 12:11:17 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef W3D_CALC_H
# define W3D_CALC_H

typedef struct			s_w3dcalc
{
	int					inc; // increments the pos for the ray
	t_vector_2d			start; // player pos in map
	t_vector_2d			player; // player pos in cell (according to the directon vector)
	t_vector_2d			end;
	t_vector_2d_d		proc_for1;
	t_vector_2d_d		processed;
	t_vector_2d			direction;
	double				distance;
}						t_w3dcalc;

#endif
