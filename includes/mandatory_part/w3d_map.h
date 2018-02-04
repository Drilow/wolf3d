#ifndef W3D_MAP_H
# define W3D_MAP_H
# include <SDL.h>
# include <helpers/shapes.h>

typedef struct			s_w3d_camera
{
	double				orientation;
	int					screendist;
	double				fov;
	double				range[2];
	t_vector_2d			direction;
	t_vector_2d			player;
}						t_w3d_camera;

typedef struct			s_w3dmap
{
	char				**map;
	t_vector_2d			size;
	t_vector_2d			pos;
	t_w3d_camera		cam;
	SDL_Surface			**walls;
}						t_w3dmap;

#endif
