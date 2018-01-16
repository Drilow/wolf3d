/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adleau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/11 14:11:02 by adleau            #+#    #+#             */
/*   Updated: 2018/01/16 13:27:28 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENGINE_H
# define ENGINE_H
# include <sdl/sdl_wrapper.h>
# include <w3d/w3d.h>

typedef struct			s_engine
{
	struct s_sdl_wrapper	mainwindow;
	struct s_w3d			w3dengine;
//	struct s_doom			doomengine;
//	struct s_duke			dukeengine;
	char					picker;
}							t_engine;

void					engine(void);

#endif
