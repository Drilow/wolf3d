/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adleau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/20 19:04:44 by adleau            #+#    #+#             */
/*   Updated: 2018/01/21 20:53:15 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <SDL.h>
#include <SDL_image.h>
#include <cleanup/cleanup.h>

/* free_sdl_wrapper
** frees everything SDL-related
 */

void			free_sdl_wrapper(t_sdl_wrapper *sdl_wrap)
{
	if (sdl_wrap->screen)
		SDL_DestroyWindow(sdl_wrap->screen);
	if (sdl_wrap->menu)
		SDL_FreeSurface(sdl_wrap->menu);
	if (sdl_wrap->wolf)
		SDL_FreeSurface(sdl_wrap->wolf);
	if (sdl_wrap->renderer)
		SDL_DestroyRenderer(sdl_wrap->renderer);
	if (sdl_wrap->tex)
		SDL_DestroyTexture(sdl_wrap->tex);
	SDL_Quit();
	IMG_Quit();
}

/* free_parser function
** frees the content of the parser
 */

void			free_parser(t_parser *parse)
{
	if (parse->parse_tab)
		;//free_2dtab(parse->parse_tab);
}

/* free_Everything function
** frees everything that was allocated, called when program exits
 */

void			free_everything(t_engine *eng, int i)
{
	free_parser(&(eng->parser));
	free_sdl_wrapper(&(eng->mainwindow));
	exit(i);
}
