/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adleau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 08:21:13 by adleau            #+#    #+#             */
/*   Updated: 2018/02/08 13:38:56 by adleau           ###   ########.fr       */
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

#include <stdio.h>

/* mandatory_part function
** entry point to the mandatory part
*/

void		mandatory_part(t_sdl_wrapper *wrap, char *path)
{
	t_wolf	wolf;

	printf("absolument rien\n");
	if (wrap == NULL)
	{
		if (!(wolf.wrap = (t_sdl_wrapper*)malloc(sizeof(t_sdl_wrapper))))
			exit(1);
		init_sdl_wrap(wolf.wrap);
	}
	else
		wolf.wrap = wrap;
	printf("rien\n");
	init_wolf(&wolf, wolf.wrap, path);
	wolf_loop(&wolf);
}
