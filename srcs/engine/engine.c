/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adleau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/11 14:10:32 by adleau            #+#    #+#             */
/*   Updated: 2018/01/23 15:42:15 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <sdl/sdl_wrapper.h>
#include <engine/engine.h>
#include <SDL.h>
#include <parser/parser.h>
#include <events/events.h>
#include <cleanup/cleanup.h>

#include <stdio.h>

/* init_parse function
** initialiszes the parse structure
 */

void				init_parse(t_parser *parse)
{
	parse->done = 0;
	parse->path = NULL;
	parse->parse_tab = NULL;
	parse->fd = -1;
	parse->beenread = -1;
	parse->parse_f = NULL;
	parse->linesread = -1;
	parse->map.size.x = 0;
	parse->map.size.y = 0;
	parse->map.pos.x = -1;
	parse->map.pos.y = -1;
	parse->map.wall_surf = NULL;

}

/* init_engine function
** initializes engine data
 */

void				init_engine(t_engine *eng)
{
	eng->picker = 0;
	eng->to_be_drawn = 0;
	eng->draw = draw_menu;
	init_sdl_wrap(&(eng->mainwindow));
	init_parse(&(eng->parser));
	if (!(eng->parser.map.walls = (char**)malloc(sizeof(char*) * 4)))
		free_everything(eng, 1);
}

/* Engine function
** Promt a choice between the different engines available
 */

void				engine(void)
{
	t_engine		eng;

	init_engine(&eng);
	while (1)
	{
		if (eng.parser.parse_f != NULL && !eng.parser.done)
		{
			parse_binds(&eng, &(eng.binds), "conf/keybinds");
			eng.parser.parse_f(&eng, eng.parser.path);
		}
		engine_loop(&eng);
	}
}
