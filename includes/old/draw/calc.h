/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adleau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/24 15:42:52 by adleau            #+#    #+#             */
/*   Updated: 2018/01/28 14:15:43 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CALC_H
# define CALC_H
# include <sdl/sdl_wrapper.h>

typedef struct		s_calc
{
	t_2dvector		limits; // limits of the map
	t_2dvector		playerpos; // on what part of case of the map the player is
	t_2dvector		posinmap; // on what case of the map the player is
	t_2dvector		direction; // the direction vector
	t_2dvector		detect; // detection until a wall is hit
	t_2dvector		increment; // increment until a wall is hit
	t_2dvector_d	scaled; // scaled coord of where the detection starts
	t_2dvector_d	firstdet; // detect the wall closest to the player
	t_2dvector_d	firstinc; // increment to the wall closest to the player
	t_2dvector_d	firstpos; // receives x and y according to the closest
}					t_calc;

#endif
