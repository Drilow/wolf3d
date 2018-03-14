/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   w3d_calc.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabessir <mabessir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/06 09:15:17 by adleau            #+#    #+#             */
/*   Updated: 2018/03/14 12:14:52 by mabessir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef W3D_CALC_H
# define W3D_CALC_H

typedef struct			s_w3dcalc
{
	int					inc;
	t_vector_2d			start;
	t_vector_2d			player;
	t_vector_2d			end;
	t_vector_2d_d		proc_for1;
	t_vector_2d_d		processed;
	t_vector_2d			direction;
	double				distance;
}						t_w3dcalc;

#endif
