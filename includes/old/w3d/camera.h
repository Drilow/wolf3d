/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adleau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/11 19:24:00 by adleau            #+#    #+#             */
/*   Updated: 2018/01/23 18:49:59 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_H
# define CAMERA_H
# include <sdl/sdl_wrapper.h>

typedef struct		s_camera
{
	double			orientation;
	int				dist_screen;
	double			fov;
	double			range_start;
	double			range_end;
	t_2dvector		direction;
	t_2dvector		player;
}					t_camera;

#endif
