/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabessir <mabessir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 08:21:13 by adleau            #+#    #+#             */
/*   Updated: 2018/03/09 16:22:07 by mabessir         ###   ########.fr       */
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

/*
** mandatory_part function
** entry point to the mandatory part
*/

void		mandatory_part(t_sdl_wrapper *wrap, char *path)
{
	t_wolf	wolf;

	if (wrap == NULL)
	{
		if (!(wolf.wrap = (t_sdl_wrapper*)malloc(sizeof(t_sdl_wrapper))))
			exit(1);
		init_sdl_wrap(wolf.wrap);
	}
	else
		wolf.wrap = wrap;
	init_wolf(&wolf, wolf.wrap, path);
	wolf_loop(&wolf);
}
