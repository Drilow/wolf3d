/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adleau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/11 14:10:32 by adleau            #+#    #+#             */
/*   Updated: 2018/01/18 13:32:50 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <sdl/sdl_wrapper.h>
#include <engine/engine.h>
#include <SDL.h>
#include <parser/parser.h>
#include <events/events.h>

#include <stdio.h>


/* init_engine function
** initializes engine data
 */

void				init_engine(t_engine *const eng)
{
	eng->picker = 0;
	init_sdl_wrap(&(eng->mainwindow));
}

/* Engine function
** Promt a choice between the different engines available
 */

void				engine(void)
{
	t_engine		eng;

	init_engine(&eng);
	/* code here */
	engine_loop(&eng);
}
