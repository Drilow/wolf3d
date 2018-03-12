/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adleau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/20 19:02:49 by adleau            #+#    #+#             */
/*   Updated: 2018/03/12 13:20:43 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLEANUP_H
# define CLEANUP_H
# include <mandatory_part/wolf.h>
# include <helpers/sdl_wrapper.h>
# include <mandatory_part/walls.h>

void			free_sdl_wrapper(t_sdl_wrapper *sdl_wrap);
void			free_wolf(t_wolf *wolf, int i);
void			free_walls(t_walls *walls);
void			free_wall(t_wall *wall);

#endif
