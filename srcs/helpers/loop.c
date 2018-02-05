#include <engine.h>
#include <full_run.h>
#include <helpers/cleanup.h>
#define EVENT_PTR eng->wrap.event
#define WIN_PTR eng->wrap.screen

/* mouseup events
** catches mouseup events and redirects to the selected game
 */

int				mouseup_events(t_engine __attribute__((unused))*eng)
{
	if (EVENT_PTR.button.button == SDL_BUTTON_LEFT)
	{
		if ((EVENT_PTR.button.x >= eng->mainmenu.w3d.start.x && EVENT_PTR.button.x <= eng->mainmenu.w3d.end.x) && (EVENT_PTR.button.y >= eng->mainmenu.w3d.start.y && EVENT_PTR.button.y <= eng->mainmenu.w3d.end.y))
		{
			return (1);
		}
	}
	return (0);
}

/* keyup_events function
** handles keyup events
*/

void			keyup_events(t_engine *eng)
{
	if (EVENT_PTR.key.keysym.sym == SDLK_ESCAPE)
	{
		free_sdl_wrapper(&(eng->wrap));
		exit(0);
	}
}

/* engine_loop function
** infinit loop used for the whole run
*/

void		engine_loop(t_engine *eng)
{
	int		ret;
	int		istrue;

	istrue = 1;
	ret = 0;
	while (istrue)
	{
		if (!eng->wrap.drawn)
			drawmainmenu(eng);
		while (SDL_PollEvent(&(EVENT_PTR)))
		{
			if (EVENT_PTR.type == SDL_QUIT)
				exit(0);
			else if (EVENT_PTR.type == SDL_KEYUP)
				keyup_events(eng);
			else if (EVENT_PTR.type == SDL_MOUSEBUTTONUP)
				if ((ret = mouseup_events(eng)))
					istrue = 0;
		}
	}
	(ret == 1) ? mandatory_part(&(eng->wrap), NULL) : bonus(&(eng->wrap));
}