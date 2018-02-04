#ifndef WOLF_H
# define WOLF_H
# include <helpers/sdl_wrapper.h>
# include <mandatory_part/w3d_parse.h>
# include <mandatory_part/w3d_map.h>
# include <mandatory_part/w3d_calc.h>

typedef struct		s_wolf
{
	t_w3dparse		parse;
	t_w3dmap		map;
	t_sdl_wrapper	*wrap;
	t_w3dcalc		calc;
}					t_wolf;

#endif
