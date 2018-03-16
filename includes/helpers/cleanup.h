/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabessir <mabessir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/20 19:02:49 by adleau            #+#    #+#             */
/*   Updated: 2018/03/16 15:53:28 by mabessir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLEANUP_H
# define CLEANUP_H
# include <mandatory_part/walls.h>
# include <mandatory_part/wolf.h>
# include <helpers/sdl_wrapper.h>

void			free_sdl_wrapper(t_sdl_wrapper *sdl_wrap);
void			free_wolf(t_wolf *wolf, int i);

#endif
