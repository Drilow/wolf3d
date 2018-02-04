#ifndef ENGINE_H
# define ENGINE_H
# include <menu.h>
# include <helpers/sdl_wrapper.h>
# include <mandatory_part/wolf.h>
# include <bonus/bonus.h>

typedef struct		s_engine
{
	t_sdl_wrapper	wrap;
	t_mainmenu		mainmenu;
	t_wolf			wolf;
	t_bonus			bonus;
	void			(*draw)(struct s_engine*);
	void			(*loop)(void*);
}					t_engine;

void		init_engine(t_engine *eng);
void		drawmainmenu(t_engine *eng);

#endif
