#include <mandatory_part/wolf.h>
#include <helpers/cleanup.h>
#include <SDL.h>
#define EVENT_PTR wolf->wrap->event
#define WIN_PTR wolf->wrap->screen

void		keyup_events_w3d(t_wolf *wolf)
{
	if (EVENT_PTR.key.keysym.sym == SDLK_ESCAPE)
	{
		free_sdl_wrapper(wolf->wrap);
		exit(0);
	}
}

/* wolf_loop function
** infinite loop to handle the w3d engine
*/

void		wolf_loop(t_wolf *wolf)
{
	int		istrue;

	istrue = 1;
	while (istrue)
	{
		printf("drawn %p\n", wolf->wrap);
		if (!wolf->wrap->drawn)
			w3d_draw(wolf);
		while (SDL_PollEvent(&(EVENT_PTR)))
		{
			if (EVENT_PTR.type == SDL_QUIT)
				exit(0);
			else if (EVENT_PTR.type == SDL_KEYUP)
				keyup_events_w3d(wolf);
/*			else if (EVENT_PTR.type == SDL_MOUSEBUTTONUP)
				if ((ret = mouseup_events(eng)))
					istrue = 0;
*/		}
	}
}
