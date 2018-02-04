/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adleau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/20 19:02:49 by adleau            #+#    #+#             */
/*   Updated: 2018/01/20 19:41:34 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLEANUP_H
# define CLEANUP_H
# include <menu.h>
# include <mandatory_part/wolf.h>
# include <bonus/bonus.h>
# include <helpers/sdl_wrapper.h>
# include <engine.h>

void			free_engine(t_engine *eng, int i);
void			free_wolf(t_wolf *wolf, int i);
void			free_menu(t_mainmenu *menu, t_sdl_wrapper *wrap, int i);
void			free_bonus(t_bonus *bonus, t_sdl_wrapper *wrap, int i);
#endif
