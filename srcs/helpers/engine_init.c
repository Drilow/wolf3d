#include <engine.h>
#include <helpers/shapes.h>

#include <stdio.h>

/* init_bonusselector function
** initializes the bonus selector for the mainmenu
*/

void		init_bonusselector(t_rect *rect)
{
	rect->start.x = WIN_WD / 2 + WIN_WD / 16;
	rect->end.x = WIN_WD - WIN_WD / 16;
	rect->start.y = WIN_HT / 9;
	rect->end.y = WIN_HT - WIN_HT / 9;
}

/* init_w3dselector function
** initializes the wolf3d selector for the mainmenu
*/

void		init_w3dselector(t_rect *rect)
{
		rect->start.x = WIN_WD / 16;
		rect->end.x = WIN_WD / 2 - WIN_WD / 16;
		rect->start.y = WIN_HT / 9;
		rect->end.y = WIN_HT - WIN_HT / 9;
}

/* init_mainmenu function
** initializes the squares for the selection in the mainmenu
*/

void		init_mainmenu(t_mainmenu *menu)
{
	init_w3dselector(&(menu->w3d));
	init_bonusselector(&(menu->bonus));
}

/* init_engine function
** initializes all the data needed for the engine
*/

void		init_engine(t_engine *eng)
{
	init_sdl_wrap(&(eng->wrap));
	init_mainmenu(&(eng->mainmenu));
}
