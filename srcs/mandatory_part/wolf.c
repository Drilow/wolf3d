/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adleau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 08:21:13 by adleau            #+#    #+#             */
/*   Updated: 2018/02/05 11:16:48 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <full_run.h>
#include <mandatory_part/wolf.h>
#include <helpers/cleanup.h>
#include <helpers/str_helpers.h>
#include <fcntl.h>
#include <SDL.h>
#include <SDL_image.h>

/* mandatory_part function
** entry point to the mandatory part
*/

void		mandatory_part(t_sdl_wrapper *wrap, char *path)
{
	t_wolf	wolf;

	if (wrap == NULL)
		init_sdl_wrap(wrap);
	else
		wolf.wrap = wrap;
	init_wolf(&wolf, wrap, path);
	wolf_loop(&wolf);
}
