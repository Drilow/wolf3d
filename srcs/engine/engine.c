/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adleau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/11 14:10:32 by adleau            #+#    #+#             */
/*   Updated: 2018/01/11 19:54:11 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <sdl/sdl_wrapper.h>
#include <engine/engine.h>
#include <SDL2/SDL.h>
#include <parser/parser.h>


/* init_engine function
** initializes engine data
 */

void				init_engine(const t_engine *const eng)
{
	eng->picker = 0;
	init_sdl_wrap(&(eng->mainmenu));
}

/* Engine function
** Promt a choice between the different engines available
 */

void				engine(void)
{
	t_engine		eng;

	init_engine(&eng);
	if (SDL_Init(SDL_INIT_EVERYTHING))
		ft_putendl("Failed to init SDL");

}
