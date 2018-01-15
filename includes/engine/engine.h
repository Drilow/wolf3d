/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adleau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/11 14:11:02 by adleau            #+#    #+#             */
/*   Updated: 2018/01/11 19:52:03 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENGINE_H
# define ENGINE_H

struct s_screen;
struct s_w3d;
struct s_doom;
struct s_duke;

typedef struct			s_engine
{
	struct s_sdl_wrapper	mainmenu;
	struct s_w3d			w3dengine;
	struct s_doom			doomengine;
	struct s_duke			dukeengine;
	char					picker;
}							t_engine;

void					engine(void);

#endif
