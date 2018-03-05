/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   w3d_map.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabessir <mabessir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 09:52:45 by adleau            #+#    #+#             */
/*   Updated: 2018/02/27 15:35:49 by mabessir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef W3D_MAP_H
# define W3D_MAP_H
# include <SDL.h>
# include <helpers/shapes.h>

typedef struct			s_w3d_camera
{
	double				orientation;
	double				angle;
	int					screendist;
	double				fov;
	double				range[2];
	t_vector_2d			direction;
	t_vector_2d			player; // pos in cell
}						t_w3d_camera;

typedef struct			s_w3dmap
{
	char				**map;
	t_vector_2d			size;
	t_vector_2d			pos; // in map
	t_w3d_camera		cam;
	t_vector_2d			walltab[4]; // positions des murs dans le fichier de texture 0-5 et 0-17 recuperes dans le fichier de map
	t_vector_2d			background;
	SDL_Surface			*textures;
	SDL_Surface			**walls; // removing soon
}						t_w3dmap;

void					init_w3dcam(t_w3d_camera *cam);
double					get_angle(double d);
void			get_direction(t_vector_2d *direction, double ray);
#endif
